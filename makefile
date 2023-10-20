.SILENT:

main: main.c
	@echo "compilation de main"
	gcc main.c -o m -framework AudioToolbox

clean:
		rm -f m