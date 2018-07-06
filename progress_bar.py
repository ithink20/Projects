import requests
import urlparse, os
from tqdm import tqdm

def is_downloadable(url):
	h = requests.get(url, allow_redirects = True)
	header = h.headers
	content_type = header.get('content-type')
	print content_type
	if 'text' in content_type:
		return False
	if 'html' in content_type:
		return False
	return True

def download(url, file_name, file_ext):
	r = requests.get(url, stream = True)
	total_size = int(r.headers['content-length'])
	block_size = 1024
	with open(file_name + file_ext, "wb") as f:
		for data in tqdm(iterable = r.iter_content(chunk_size = block_size), total = total_size/block_size, unit = 'KB'):
			f.write(data)


def main():
	#url = 'http://www.peoplelikeus.org/piccies/codpaste/codpaste-teachingpack.pdf'

	url = 'https://c2.staticflickr.com/8/7151/6760135001_58b1c5c5f0_b.jpg'

	#get filename and file-extension.
	path = urlparse.urlparse(url).path
	file_data = os.path.basename(path)
	file_name, file_ext = os.path.splitext(file_data)

	ok = is_downloadable(url)
	if ok:
		print 'Downloading'
		download(url, file_name, file_ext)

if __name__ == '__main__':
	main()
