import sys
import os

def convert_names(text):
    words = text.split(" ")
    result = ""
    for word in words:
        if "*" == word:
            result += "ptr"
        else:
            result += f"{word}_"
    result = result.replace("*", "_ptr").rstrip("_")
    print("Text:", text, "Result:", result)
    return result

def expand_type_wrappers(text):
    x = 0
    struct_of = "struct"
    ptr_to = "ptr_to"
    text = text.rstrip(')')
    size = len(text)
    for x in range(size):
        if len(text[x:]) > len(struct_of) and struct_of in text[x:x+len(struct_of)]:
            return "struct_{}".format(expand_type_wrappers(text[x+len(struct_of)+1:]))
        elif len(text[x:]) > len(ptr_to) and ptr_to in text[x:x+len(ptr_to)]:
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
                sys.exit(1)
            vector_mappings.append(mapping)

    return vector_mappings

def write_header(header_file, defines, generators, generics, conversions):
    with open(header_file, "w") as outfile:
        guard = os.path.basename(header_file).upper().replace('.', '_')
        outfile.write(f"#ifndef {guard}\n")
        outfile.write(f"#define {guard}\n")
        outfile.write("\n\n")
        outfile.write(f"/* Mappings from contained type to vector type */\n")
        #outfile.write(defines)
        outfile.write("\n\n")
        outfile.write(f"/* Generate wrappers for vector of contained type */\n")
        outfile.write(generators)
        outfile.write("\n\n")
        outfile.write(f"/* Map vector types to that vectors implementation */\n")
        outfile.write(generics)
        outfile.write("\n\n")
        outfile.write(f"/* Map contained types to vector creation function */\n")
        outfile.write(conversions)
        outfile.write("\n\n")
        outfile.write(f"#endif /* {guard} */")

def write_source(source_file, impls):
    with open(source_file, "w") as outfile:
        outfile.write(f"#define VECTOR_HELPERS_INCLUDE_IMPL\n")
        outfile.write(f"#include \"vectors.h\"\n\n")
        outfile.write(f"{impls}")

def generate_header_mappings(mappings):
    # first lets generate type defines
    defines = []
    define_blob = ""
    vector_generators = []
    vector_generator_blob = ""
    vector_implementations = []
    vector_implementation_blob = ""
    vector_generics = []
    vector_generic_blob = "#define VECTOR_GENERICS(a, b) \\\n"
    type_to_vector_conversions = []
    vector_conversion_blob = "#define TYPE_TO_VECTORS(post) \\\n"
    for mapping in mappings:
        defines.append(f"#define VEC_TYPE_{mapping[3]} {mapping[1]}")
        vector_generators.append(f"DECLARE_VECTOR_FOR_TYPE({mapping[1]}, {mapping[0]}, true)")
        vector_implementations.append(f"GENERATE_VECTOR_FUNCTION_DEFINITIONS({mapping[1]}, {mapping[0]}, true)")
        vector_generics.append(f"VECTOR_GENERIC(a, {mapping[1]}, b)")
        type_to_vector_conversions.append(f"TYPE_TO_VECTOR({mapping[0]}, {mapping[1]}, post)")

#    print("\nDefines:") 
    for define in defines:
        define_blob += f"{define}\n"
#        print(define)

#    print("\nGenerators:") 
    for generator in vector_generators:
        vector_generator_blob += f"{generator}\n"
#        print(generator)
    
    for implementation in vector_implementations:
        vector_implementation_blob += f"{implementation}\n"

#    print("\nGenerics:") 
    last = len(vector_generics) - 1
    for ii, generic in enumerate(vector_generics):
        if ii != last:
            vector_generic_blob += f"    {generic}, \\\n"
        else:
            vector_generic_blob += f"    {generic}\n"
#        print(generic)

#    print("\nConversion:") 
    last = len(type_to_vector_conversions) - 1
    for ii, conversion in enumerate(type_to_vector_conversions):
        if ii != last:
            vector_conversion_blob += f"    {conversion}, \\\n"
        else:
            vector_conversion_blob += f"    {conversion}\n"
#        print(conversion)

    print("")

    print(define_blob)
    print(vector_generator_blob)
    print(vector_generic_blob)
    print(vector_conversion_blob)

    return define_blob, \
        vector_generator_blob,\
        vector_generic_blob,\
        vector_conversion_blob, \
        vector_implementation_blob


if __name__ == "__main__":
    if len(sys.argv) != 4:
        print("Usage:", sys.argv[0], "[vector_file] [header_file] [source_file]")
        sys.exit(1)

    vec_file = sys.argv[1]
    header_file = sys.argv[2]
    source_file = sys.argv[3]
    vector_mappings = read_mappings(vec_file)

    for mapping in vector_mappings:
        mapping.append(convert_names(mapping[0]))
        mapping.append(convert_names(mapping[0]))
    
    defines, generators, generics, conversions, impls = generate_header_mappings(vector_mappings)

    write_header(header_file, defines, generators, generics, conversions)
    write_source(source_file, impls)



