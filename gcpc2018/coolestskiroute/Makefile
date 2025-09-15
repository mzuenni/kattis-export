.SILENT:

include ../Makefile.single

# Convenience targets
validate-input:
	make test ARGS="-p data -l info"

solution: build/solution.pdf

build/solution.pdf: solution/solution.en.tex problem.yaml.tex
	mkdir -p build
	problem2pdf . -solution -o build/solution.pdf 

%.yaml.tex: %.yaml
	cat $< | sed '/^\#/d' | sed 's/\([a-z]*\): /\\problem\1\{/g' | sed 's/\\problem.*/&}/g' > $@

clean:
	echo "cleaning up"
	rm -rf build/
	find . -name '*.class' -delete;
	find . -name 'a.out' -delete;

# Generator for .in-files
seeds := $(wildcard data/secret/*.desc)
seeded-infiles := $(seeds:.desc=.in)
seeded-infiles := $(sort ${seeded-infiles})
generator := $(wildcard generators/*Generator.java)
generator := $(notdir ${generator})
generator-compiled := $(generator:.java=.class)
generator := $(generator:.java=)

input: $(seeded-infiles)

%.in: %.desc generators/$(generator-compiled)
	echo "generating input using $<"
	cat $< | sed -e 's/#.*//' | java -cp generators ${generator} > $@

%.class: %.java
	echo "compiling $<"
	javac $<

# Generator fow .ans-files
solutions := $(wildcard submissions/accepted/*.java)
solutions += $(wildcard submissions/accepted/*.cpp)
solutions += $(wildcard submissions/accepted/*.cc)
solutions := $(sort ${solutions})
solution := $(firstword ${solutions})
javasol := $(notdir ${solution})
javasol := $(javasol:.java=)
solution-compiled := $(solution:.java=.class)
solution-compiled := $(solution-compiled:.cpp=.outcpp)
solution-compiled := $(solution-compiled:.cc=.outcc)
infiles := $(wildcard data/sample/*.in)
infiles += $(wildcard data/secret/*.in)
infiles += ${seeded-infiles}
infiles := $(sort ${infiles})
ansfiles := $(infiles:.in=.ans)

output: $(ansfiles)

%.ans: %.in $(solution-compiled)
	echo "generating output for $<"
ifneq (.class,$(findstring .class,$(solution-compiled)))
	# cpp solution
	./${solution-compiled} < $< > $@ 
else
	# java file
	java -cp submissions/accepted ${javasol} < $< > $@ 
endif

%.outcpp: %.cpp
	echo "compiling $<"
	g++ -std=c++11 -o $@ $<
	
%.outcc: %.cc
	echo "compiling $<"
	g++ -std=c++11 -o $@ $<
