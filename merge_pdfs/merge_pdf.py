import os
import re
from PyPDF2 import PdfFileWriter, PdfFileReader


def custom_sort(first, second):
    b1 = os.path.basename(first)
    b2 = os.path.basename(second)

    b1 = os.path.splitext(b1)[0]
    b2 = os.path.splitext(b2)[0]

    rg = "chapter(\d+)"
    m1 = re.search(rg, b1, re.IGNORECASE)
    m2 = re.search(rg, b2, re.IGNORECASE)

    group_1 = int(m1.group(1))
    group_2 = int(m2.group(1))
    return cmp(group_1, group_2)

def main():
	print "merging in progress...."
	#path - specify, if files are not in same code running dir.
	files = [os.path.join("path",file) for file in os.listdir("path")]
	output = PdfFileWriter()
	# files.sort() this will sort lexicographically that we don't want like 
	#  chapter1 then chapter11 but we want chapter2 so. make custom sort()
	files.sort(custom_sort)

	for f in files:
    	#print "appending %s" % f
    	input = PdfFileReader(open(f,"rb"))
    	for page in range(0,input.getNumPages()):
        	#print "\tadding page %d" % page
        	output.addPage(input.getPage(page))

	outputFile = "merged_output.pdf"
	outStream = open(outputFile,"wb")
	output.write(outStream)
	outStream.close()
	print "merging completed!"



if __name__ == __main__:
	main()