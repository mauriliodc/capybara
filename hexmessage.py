
def asciiDigitToHex(c):
	if ord(c) < ord('A'):
		return ord(c)-ord('0')
	return ord(c)-ord('A')+10

def readHex(message,destination):
	for char in message:
		d=asciiDigitToHex(char)<<4
		d|=asciiDigitToHex(char)
		destination+=chr(d)
		

destination=""
message="018801000000000000000000000000008000000000AD68923700000000D80237B800000000000000000000000000000000000000000000"
readHex(message,destination)
print destination
