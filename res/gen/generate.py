import sqlite3
import re
import csv
import sys, os
from collections import defaultdict

from pprint import PrettyPrinter

pp = PrettyPrinter(indent=2)

def get_jtitle( row ):
	try:
		title = row[0].split(':')[0].strip()
	except: pass
	return title

def get_jdesignations( row ):
	desigs = {}
	try:
		desigs = {d.strip():{} for d in row[0].split(':')[1].split(',') if d.strip()}
	except: pass
	return desigs

def get_jtoolkind( header ):
	header = header.split(':')
	tool = header[0].strip()
	kind = re.search('\((.*)\)', header[1])
	if kind: kind = kind.group(1)
	else: kind = ''

	return tool, kind.lower()

def get_jfeedspeed( cell ):
	cell = [ float(c.strip()) for c in cell.split() if c.strip() ]
	return cell

def get_jhardness( row ):
	cell = row[1]
	cell = {c.strip():{} for c in cell.split() if c.strip()}
	return cell

def generate_json( data ):
	rstart,rend = 0, 16
	cstart,cend = 3, 19

	json = {}
	for i,row in enumerate(data[rstart:rend]):
		title			= get_jtitle(row)
		designations	= get_jdesignations(row)
		hardnesses		= get_jhardness(row)

		if title and designations:
			tdata = json.setdefault(title,{})
			for desig in designations:
				ddata = tdata.setdefault(desig,{})
				for hard in hardnesses:
					hdata = ddata.setdefault(hard,{})

					for j,col in enumerate(row[cstart:cend]):
						header = data[0][j+cstart]
						tool, kind  = get_jtoolkind( header )
						feed, speed = get_jfeedspeed( col )

						odata = hdata.setdefault(tool,{})
						kdata = odata.setdefault(kind,{})
						fdata = kdata.setdefault('feed',[])
						sdata = kdata.setdefault('speed',[])

						fdata.append(feed)
						sdata.append(speed)

	return json

def generate_output_str( data, buf='\t\t'):
	out = ''
	s = '{0}{{"{1}",{{\n{2}\n{0}}}}}'.format
	if not isinstance(data,list):
		for i,item in enumerate(data.items()):
			k,v = item
			out += s(buf,k,generate_output_str(v, buf + '\t'))
			if i == len(data)-1: out += '\n'
			else: out += ',\n'
	else:
		out += buf + ','.join(['"{}"'.format(w) for w in data])

	with open('data.hpp','w') as f:
		f.write('#ifndef MCALC_STATIC_DATA_HPP\n')
		f.write('#define MCALC_STATIC_DATA_HPP\n\n')
		f.write('#include "json.hpp"\n\n')
		f.write('namespace static_data {{\n\tnlohmann::json DATA = {{\n{}\n\t}}; \n}}'.format(out))
		f.write('\n\n#endif')

	return out

def generate_output_db( data ):
	dbfile = 'mcalc.db'
	if (os.path.exists(dbfile)):
		os.remove(dbfile)

	conn = sqlite3.connect('mcalc.db')
	cur = conn.cursor()

	cur.execute('''CREATE TABLE materials
             (description text, designation text, hardness text, tool text, grade text, max_feed real, min_feed real, max_sfpm real, min_sfpm real)''')
	cur.execute("CREATE TABLE settings (profile text, theme text)")
	cur.execute("INSERT INTO settings VALUES (\"default\",\"\")")

	for desc,a in data.items():
		for desg,b in a.items():
			for hard,c in b.items():
				hard = '-'.join([i for i in re.split('[^\d]',hard) if i])
				for tool,d in c.items():
					for grade,e in d.items():
						max_s = max(e["speed"])
						min_s = min(e["speed"])

						max_f = max(e["feed"])
						min_f = min(e["feed"])

						command = "INSERT INTO materials VALUES (\"{}\",\"{}\",\"{}\",\"{}\",\"{}\",{},{},{},{})".format(
							desc,
							desg,
							hard,
							tool,
							grade,
							max_f,
							min_f,
							max_s,
							min_s
						)

						cur.execute(command)
	conn.commit()
	conn.close()

def generate( fn ):
	with open(fn,newline='') as f:
		data = list(list(r) for r in csv.reader(f))
		code = generate_json(data)
		generate_output_db(code)
		#generate_output_str(code)



if __name__=='__main__':
	if len(sys.argv) > 1:
		fname = sys.argv[1]
		generate(fname)
