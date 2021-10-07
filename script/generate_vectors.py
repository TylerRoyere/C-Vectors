import sys

def convert_pointers(text):
    x = len(text)-1
    while x >= 0:
        if text[x] == '*':
            return "ptr_to({})".format(convert_pointers(text[0:x]))
        x = x - 1
    return text.strip()

def convert_structs(text):
    struct = "struct"
    x = 0
    size = len(text)
    while x < size:
        #print(x)
        #print(struct, text[x:])
        if len(text[x:]) > len(struct) and struct in text[x:x+len(struct)]:
            print("Text left:", text[x:])
            return "{}struct_of({})".format(text[:x], convert_structs(text[x+len(struct):]))
        x = x + 1
    return text.strip()

def expand_type_wrappers(text):
    x = 0
    struct_of = "struct_of"
    ptr_to = "ptr_to"
    text = text.rstrip(')')
    size = len(text)
    for x in range(size):
        if len(text[x:]) > len(struct_of) and struct_of in text[x:x+len(struct_of)]:
            print(text[x+len(struct_of)+1:])
            return "struct_{}".format(expand_type_wrappers(text[x+len(struct_of)+1:]))
        elif len(text[x:]) > len(ptr_to) and ptr_to in text[x:x+len(ptr_to)]:
            #print("no")
            return "{}_ptr".format(expand_type_wrappers(text[x+len(ptr_to)+1:]))

    return text.strip()
    

def read_mappings(file):
    vector_mappings = []
    with open(vec_file, "r") as infile:
        contents = infile.readlines()
        lines = [line.rstrip() for line in contents]
        lines = [line for line in lines if line]

        for ii, line in enumerate(lines):
            mapping = line.split(",");
            mapping = [text.strip() for text in mapping]
            if len(mapping) != 2:
                print("Invalid mapping in", vec_file, "line", ii)
            vector_mappings.append(mapping)

    return vector_mappings

def generate_header_mappings(mappings):
    # first lets generate type defines
    defines = []
    vector_generators = []
    vector_generics = []
    type_to_vector_conversions = []
    for mapping in mappings:
        defines.append(f"#define VEC_TYPE_{mapping[3]}\t{mapping[1]}")
        vector_generators.append(f"GENERATE_VECTOR_FOR_TYPE({mapping[3]}, {mapping[0]}, true)")
        vector_generics.append(f"VECTOR_GENERIC(a, {mapping[1]}, b)")
        type_to_vector_conversions.append(f"TYPE_TO_VECTOR({mapping[0]}, {mapping[1]}, post)")

    print("\nDefines:") 
    for define in defines:
        print(define)

    print("\nGenerators:") 
    for generator in vector_generators:
        print(generator)

    print("\nGenerics:") 
    for generic in vector_generics:
        print(generic)

    print("\nConversion:") 
    for conversion in type_to_vector_conversions:
        print(conversion)


if __name__ == "__main__":
    if len(sys.argv) < 3:
        print("Usage:", sys.argv[0], "[vector_file] [header_file]")
        sys.exit(1)

    vec_file = sys.argv[1]
    header_file = sys.argv[2]
    vector_mappings = read_mappings(vec_file)

    for mapping in vector_mappings:
        print(mapping[0], "->", mapping[1])

    print("Converting pointers")
    for mapping in vector_mappings:
        mapping.append(convert_pointers(mapping[0]))

    for mapping in vector_mappings:
        print(mapping[0], "->", mapping[1])

    print("Converting structures")
    for mapping in vector_mappings:
        mapping[2] = convert_structs(mapping[2])

    for mapping in vector_mappings:
        print(f"({mapping[0]}, {mapping[2]}) -> {mapping[1]}")

    print("Unwrapping")
    for mapping in vector_mappings:
       mapping.append(expand_type_wrappers(mapping[2]))

    for mapping in vector_mappings:
        print(f"( {mapping[0]}, {mapping[2]}, {mapping[3]} ) -> {mapping[1]}")
    
    generate_header_mappings(vector_mappings)



