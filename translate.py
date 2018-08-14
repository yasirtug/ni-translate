from googletrans import Translator

translator = Translator()

file = open(".ask", "r")
dest = file.readline()[:-1]
src = file.readline()[:-1]
text = file.read()
file.close()

result = translator.translate(text, dest, src)

file = open(".result", "w")
file.write(result.dest + '\n' + result.src + '\n' + result.text)
file.close()    