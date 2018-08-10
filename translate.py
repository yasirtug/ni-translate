from googletrans import Translator
import sys

translator = Translator()

length = len(sys.argv)
dest = 'en' if (length < 3) else sys.argv[2]
src = 'auto' if (length < 4) else sys.argv[3]

result = translator.translate(sys.argv[1], dest, src)

file = open(".result", "w")
file.write(result.dest + '\n' + result.src + '\n' + result.text)
file.close()