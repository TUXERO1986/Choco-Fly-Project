import os

output_file = "proyecto_completo.txt"
extensiones = ('.cpp', '.h', '.hpp')

with open(output_file, 'w', encoding='utf-8') as outfile:
    for root, dirs, files in os.walk('.'):
        for file in files:
            if file.endswith(extensiones):
                filepath = os.path.join(root, file)
                # Escribe el nombre del archivo como separador
                outfile.write(f"\n{'='*50}\n")
                outfile.write(f"Archivo: {filepath}\n")
                outfile.write(f"{'='*50}\n\n")
                try:
                    with open(filepath, 'r', encoding='utf-8') as infile:
                        outfile.write(infile.read())
                except Exception as e:
                    outfile.write(f"// Error al leer el archivo: {e}\n")

print(f"Archivos unidos con éxito en {output_file}")