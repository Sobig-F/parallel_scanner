source_dir = src
out_dir = out

all: clean
	mkdir $(out_dir)
	gcc -Werror -Wextra $(source_dir)/*.c $(source_dir)/*.h -o $(out_dir)/scanner

clean:
	rm -rf $(out_dir)