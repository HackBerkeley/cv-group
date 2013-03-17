from SimpleCV import *

class NumeralExtractor:

	def __init__(self):
		self.numerals = []

	def extract(self, image):
		threshIm = image.threshold(155)
		blobs = threshIm.findBlobs()
		if blobs:
			for b in blobs:
				b.draw(color=Color.RED)
				self.numerals.append(b)
		threshIm.show()
		print self.numerals
	

def main():
	numExt = NumeralExtractor()
	im = Image("RowReduce.png")
	numExt.extract(im)

main()
