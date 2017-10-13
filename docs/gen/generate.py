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
	cstart,cend = 4, 15

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


					#if tool not in v: v[tool] = {}
					#if kind not in v[tool]: v[tool][kind] = {}
					#for hard in hardnesses:
					#	if hard not in v[tool][kind]:
					#		v[tool][kind][hard] = {}

						#if 'feeds' not in v[tool][kind][hard]:
						#	v[tool][kind][hard]['feeds'] = []
						#if 'speeds' not in v[tool][kind][hard]:
						#	v[tool][kind][hard]['speeds'] = []

						#v[tool][kind][hard]['feeds'].append(feed)
						#v[tool][kind][hard]['speeds'].append(speed)

	return json


def generate_cpp( fn ):
	with open(fn,newline='') as f:
		data = list(list(r) for r in csv.reader(f))
		code = generate_json(data)

		pp.pprint(code)



if __name__=='__main__':
	if len(sys.argv) > 1:
		fname = sys.argv[1]
		generate_cpp(fname)
