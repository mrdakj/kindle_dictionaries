import os
import sys
import shutil
import googletrans

source_dir = "source"
target_dir = "target"

lang = input()
valid = False
for k, v in googletrans.LANGUAGES.items():
    if lang == v or lang == k:
        valid = True
        print(k, v)

if not valid:
    print("Language %s not supported. Supported languages:%s." % (lang, googletrans.LANGUAGES))
    sys.exit(1)

translator = googletrans.Translator()

if os.path.exists(target_dir):
    shutil.rmtree(target_dir)
os.mkdir(target_dir);

for file in sorted(os.listdir(source_dir)):
   with open( os.path.join(source_dir, file) ,"r") as fd:
       result = translator.translate(fd.read(), src = 'english', dest = lang)
       with open( os.path.join(target_dir, file), 'w') as f:
           f.write(result.text)
