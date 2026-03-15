CFLAGS=-Wall -ggdb -Wextra -pedantic
HASHMAP_LIB_INCLUDE=./lib/vendor/hashmap.c/
HASHMAP_LIB_C=./lib/vendor/hashmap.c/hashmap.c
HASHMAP_LIB_H=./lib/vendor/hashmap.c/hashmap.h
HASHMAP_LIB_O=./build/hashmap.o

all: hashmap_lib lowest_common_ancestor topk_frequent valid_anagrams is_anagram

lowest_common_ancestor:
	cc $(CFLAGS) src/lowest_common_ancestor.c -o build/lowest_common_ancestor.out

topk_frequent:
	cc $(CFLAGS) src/topk_frequent.c -o build/topk_frequent.out

valid_anagrams: $(HASHMAP_LIB_O)
	cc $(CFLAGS) src/valid_anagrams.c $(HASHMAP_LIB_O) -o build/valid_anagrams.out -I$(HASHMAP_LIB_INCLUDE)

hashmap_lib: $(HASHMAP_LIB_C) $(HASHMAP_LIB_H)
	cc $(CFLAGS) -c $(HASHMAP_LIB_C) -o $(HASHMAP_LIB_O)

valid_anagrams_no_lib:
	cc $(CFLAGS) src/valid_anagrams_no_lib.c -o build/valid_anagrams_no_lib.out

is_anagram:
	cc $(CFLAGS) src/is_anagram.c -o build/is_anagram.out

clean:
	rm -rf build/*.out build/*.o
