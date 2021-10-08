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
            return "{}struct({})".format(text[:x], convert_structs(text[x+len(struct):]))
        x = x + 1
    return text.strip()

def expand_type_wrappers(text):
    x = 0
    struct_of = "struct"
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
    

def read_mappings(vec_file):
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

def write_header(header_file, defines, generators, generics, conversions):
    with open(header_file, "w") as outfile:
        outfile.write(defines)
        outfile.write("\n\n")
        outfile.write(generators)
        outfile.write("\n\n")
        outfile.write(generics)
        outfile.write("\n\n")
        outfile.write(conversions)
        outfile.write("\n\n")


def generate_header_mappings(mappings):
    # first lets generate type defines
    defines = []
    define_blob = ""
    vector_generators = []
    vector_generator_blob = ""
    vector_generics = []
    vector_generic_blob = "#define VECTOR_GENERICS(a, b) \\\n"
    type_to_vector_conversions = []
    vector_conversion_blob = "#define TYPE_TO_VECTORS(post) \\\n"
    for mapping in mappings:
        defines.append(f"#define VEC_TYPE_{mapping[3]} {mapping[1]}")
        vector_generators.append(f"GENERATE_VECTOR_FOR_TYPE({mapping[2]}, {mapping[0]}, true)")
        vector_generics.append(f"VECTOR_GENERIC(a, {mapping[1]}, b)")
        type_to_vector_conversions.append(f"TYPE_TO_VECTOR({mapping[0]}, {mapping[1]}, post)")

    print("\nDefines:") 
    for define in defines:
        define_blob += f"{define}\n"
        print(define)

    print("\nGenerators:") 
    for generator in vector_generators:
        vector_generator_blob += f"{generator}\n"
        print(generator)

    print("\nGenerics:") 
    last = len(vector_generics) - 1
    for ii, generic in enumerate(vector_generics):
        if ii != last:
            vector_generic_blob += f"    {generic}, \\\n"
        else:
            vector_generic_blob += f"    {generic}\n"
        print(generic)

    print("\nConversion:") 
    last = len(type_to_vector_conversions) - 1
    for ii, conversion in enumerate(type_to_vector_conversions):
        if ii != last:
            vector_conversion_blob += f"    {conversion}, \\\n"
        else:
            vector_conversion_blob += f"    {conversion}\n"
        print(conversion)

    print("")

    print(define_blob)
    print(vector_generator_blob)
    print(vector_generic_blob)
    print(vector_conversion_blob)

    return define_blob, vector_generator_blob, vector_generic_blob, vector_conversion_blob


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
    
    defines, generators, generics, conversions = generate_header_mappings(vector_mappings)

    write_header(header_file, defines, generators, generics, conversions)



