.PHONY: doc

doc:
	doxygen Doxyfile
	cd latex && make
	mv latex/refman.pdf doc/docs.pdf
	rm -rf latex
