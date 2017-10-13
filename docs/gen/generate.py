import re
import csv
import sys
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
	rstart,rend = 0, 11
	cstart,cend = 3, 16

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
						if tool == 'HSS':
							values = get_jfeedspeed( col )
							odata = hdata.setdefault(tool,[])
							odata.extend(values)

						else:
							feed, speed = get_jfeedspeed( col )

							odata = hdata.setdefault(tool,{})
							kdata = odata.setdefault(kind,{})
							fdata = kdata.setdefault('feed',[])
							sdata = kdata.setdefault('speed',[])

							fdata.append(feed)
							sdata.append(speed)

	return json

def generate_output_str( data, buf='\t\t', readable=False ):
	out = ''
	if readable:
		b,n = buf, '\n'
		s = '{0}{{"{1}",{{\n{2}\n{0}}}}}'.format
	else:
		b,n = '',''
		s = '{0}{{"{1}",{{{2}{0}}}}}'.format
	if not isinstance(data,list):
		for i,item in enumerate(data.items()):
			k,v = item
			out += s(b,k,generate_output_str(v, b + '\t'))
			if i == len(data)-1: out += n
		else: out += ',{}'.format(n)
	else:
		out += b + ','.join(['"{}"'.format(w) for w in data])

	with open('data.hpp','w') as f:
		f.write('namespace mcalc {{\n\tjson material = {{\n{}\n\t}}; \n}}'.format(out))

	return out

def generate_cpp( fn ):
	with open(fn,newline='') as f:
		data = list(list(r) for r in csv.reader(f))
		code = generate_json(data)
		sout = generate_output_str(code)



if __name__=='__main__':
	if len(sys.argv) > 1:
		fname = sys.argv[1]
		generate_cpp(fname)
