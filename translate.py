from googletrans import Translator
import sys, os

translator = Translator()
path = os.path.dirname(os.path.abspath(__file__)) + '/'

file = open(path + ".ask", "r")
dest = file.readline()[:-1]
src = file.readline()[:-1]
text = file.read()
file.close()

result = translator.translate(text, dest, src)

file = open(path + ".result", "w")
file.write(result.dest + '\n' + result.src + '\n' + result.text)
file.close()    