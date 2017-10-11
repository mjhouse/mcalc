import re
import csv
import sys

def gen_materials_json( reader ):
	code = "json material = {"
	asls = [r for r in reader]
	data = {}
	for row in asls[1:-1]:
		try:
			hards = [v.strip() for v in re.split('(\n|\t|\s+)',row[1]) if v.strip()]
			string = row[0].replace('\n',' ')
			if string.strip():
				title = string.split(':')[0].strip()
				desigs = [d.strip() for d in string.split(':')[1].split(',') if d.strip()]
				if title and desigs:
					if title not in data:
						data[title] = {}
					data[title].update({d:hards for d in desigs if d not in data[title]})
		except:
			pass


	for title,desigs in data.items():
		print(title)
		for d in desigs:
			print("	"+d + ": " + str(desigs[d]))


def generate_cpp( fn ):
	with open(fn,newline='') as f:
		reader = csv.reader(f)
		code = gen_materials_json(reader)



if __name__=='__main__':
	if len(sys.argv) > 1:
		fname = sys.argv[1]
		generate_cpp(fname)
