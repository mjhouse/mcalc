import re
import csv
import sys

TITLES = 0
DATA_START = 1
DATA_END = 10

COL_LENGTH = 10
DATA_RANGE = range(1,10)
TOOL_RANGE = range(2,14)

def gen_materials_json( csv ):
	code = "json material = {\n"
	data = {}
	for row in csv[1:-1]:
		try:
			hards = [v.strip() for v in re.split('(\n|\t|\s+)',row[1]) if v.strip()]
			string = row[0].replace('\n',' ')
			if string.strip():
				s_list = string.split(':')
				title = s_list[0].strip()
				desigs = [d.strip() for d in s_list[1].split(',') if d.strip()]
				if title and desigs:
					if title not in data:
						data[title] = {}
					for d in desigs:
						if d not in data[title]: data[title][d] = []
						for h in hards:
							if h not in data[title][d]:
								data[title][d].append(h)

		except:
			pass


	for j,item in enumerate(data.items()):
		title,desigs = item
		code += '\t{{"{}",{{\n'.format(title)
		for i,d in enumerate(desigs):
			code += '\t\t{{"{}",{{{{ "hardness", {{"{}"}}}}}}}}'.format(d,'","'.join(desigs[d]))
			if i == len(desigs)-1: code += '\n'
			else: code += ',\n'

		if j == len(data.items())-1: code += '\n\t}}\n'
		else: code += '\n\t}},\n'
	code += '};'

	return code

def get_column(idx,csv):
	col = []
	for row in csv[:-1]:
		col.append(row[idx])
	return col

def get_designations(idx,csv):
	global DATA_RANGE

	cell = csv[idx][0]
	data = []
	if idx in DATA_RANGE:
		data = [d.strip() for d in cell.split(':')[1].split(',') if d.strip()]
	return data


def gen_tool_json(csv):
	global DATA_START
	global DATA_END
	global TOOL_RANGE
	data = {}
	for i in TOOL_RANGE:
		col = get_column(i,csv)

		header = col[0].split(':')
		name = header[0].strip()
		_type = re.search('\((.*)\)', header[1])
		if not _type: continue

		_type = _type.group(1)
		data[name].update({_type:{}})
		#for j,contents in enumerate(col[1:10]):
		#	d = get_designations(j,csv)

	print(data)


def generate_cpp( fn ):
	with open(fn,newline='') as f:
		data = list(list(r) for r in csv.reader(f))
		material_code	= gen_materials_json(data)
		tool_code		= gen_tool_json(data)



if __name__=='__main__':
	if len(sys.argv) > 1:
		fname = sys.argv[1]
		generate_cpp(fname)
