import re

print(re.sub("^([a-zA-Z]*[aeiou])?([^aeiou])*$",r"\1ntry",raw_input()))
