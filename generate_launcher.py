import sys
import os
import stat


app_name = sys.argv[1]
binary_path = sys.argv[2]
resources_path = sys.argv[3]
launcher_path = sys.argv[4]

print('-- Generating {} launcher'.format(app_name))

launcher_file = '{}/{}.sh'.format(launcher_path, app_name)

with open(launcher_file, 'w') as file:
    file.write('{} "{}"'.format(binary_path, resources_path))
