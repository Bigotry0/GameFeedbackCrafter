import os
import re

normal_end_punctuation = (',', '.', ':', ';', '!', '?', ')', ']')

def collect_header_files(directory):
    header_files = {}
    for root, _, files in os.walk(directory):
        for file in files:
            if file.endswith('.h'):
                dir_name = os.path.basename(root)
                if dir_name not in header_files:
                    header_files[dir_name] = []
                header_files[dir_name].append(os.path.join(root, file))
    return header_files

def parse_header_file(file_path):
    with open(file_path, 'r', encoding='utf-8') as file:
        content = file.read()
    
    class_pattern = re.compile(r'/\*\*(.*?)\*/\s*UCLASS\([^)]*\)+\s*class\s+(?:\w+_API\s+)?(\w+)', re.DOTALL)
    field_pattern = re.compile(r'/\*\*(.*?)\*/\s*UPROPERTY\([^)]*\)+\s*(\w+\*?)\s+(\w+)(?:\s*=\s*[^;]+)?;', re.DOTALL)
    
    classes = class_pattern.findall(content)
    class_fields = {}
    
    for class_comment, class_name in classes:
        # 只保留第一个多行注释
        class_comment = class_comment.split('/**', 10000)[-1]
        class_start = content.find(class_name)
        class_end = content.find('};', class_start) + 2
        class_content = content[class_start:class_end]
        
        fields = field_pattern.findall(class_content)
        processed_fields = []
        for field_comment, type_name, item_name in fields:
            if field_comment:
                field_comment = field_comment.split('/**', 10000)[-1]
            else:
                field_comment = ""
            processed_fields.append((field_comment, type_name, item_name))
        
        class_fields[class_name] = (class_comment, processed_fields)
    
    return class_fields

def format_comment(comment):
    if not comment:
        return ""
    lines = comment.strip().split('\n')
    formatted_comment = ""
    for line in lines:
        line = line.strip().lstrip('*').strip()
        if line and not line.endswith(normal_end_punctuation):
            line += ' \\\n\t'
        else:
            line += ' '
        formatted_comment += line
    return formatted_comment.strip()

def generate_documentation(class_fields):
    documentation = ""
    for class_name, (class_comment, fields) in class_fields.items():
        effect_name = class_name  # Default to class name if parsing fails
        effect_type = "Unknown"  # Default to Unknown if parsing fails
        
        # Try to parse class_name in the format UGFE_{effect_type}_{effect_name}
        match = re.match(r'UGFE_(\w+)_(\w+)', class_name)
        if match:
            effect_type, effect_name = match.groups()
        else:
            # Try to parse class_name in the format UGFE_{AnyString+Base}
            match = re.match(r'UGFE_(\w+Base)', class_name)
            if match:
                effect_name = match.group(1)
                effect_type = "BaseClass"
        
        description = format_comment(class_comment)
        documentation += f"## {effect_name}\n"
        documentation += f"**Class Name:** {class_name} \\\n"
        documentation += f"**Effect Type:** {effect_type} \\\n"
        documentation += f"**Description:** {description} \\\n"
        if(len(fields) > 0):
            documentation += "**Configuration:**\n"
            
            for field_comment, type_name, item_name in fields:
                field_description = format_comment(field_comment)
                documentation += f"- `{item_name}`: `{type_name}`\n\t{field_description}\n"
        
        # documentation += "**Showcase:**\n"
        
        documentation += "\n"
    
    return documentation

def save_documentation(output_directory, dir_name, documentation):
    output_path = os.path.join(output_directory, f"{dir_name}.md")
    with open(output_path, 'w', encoding='utf-8') as file:
        file.write(documentation)

if __name__ == "__main__":
    base_dir = os.getcwd()
    source_directory = os.path.join(base_dir, "Source", "GameFeedbackEffect")
    output_directory = os.path.join(base_dir, "doc", "Effect")
    header_files = collect_header_files(source_directory)
    
    for dir_name, files in header_files.items():
        if dir_name == "Private" or dir_name == "Public":
            continue
        combined_documentation = ""
        for header_file in files:
            class_fields = parse_header_file(header_file)
            documentation = generate_documentation(class_fields)
            combined_documentation += documentation
        save_documentation(output_directory, dir_name, combined_documentation)
