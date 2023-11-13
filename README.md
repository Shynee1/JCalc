# JCalc
Simple CLI tool to parse math expressions. \
Follows the order of operations / PEMDAS.
## **Features**
- Tokenize string expression
- Create AST using Pratt Parsing
- Evaluate AST to double

## **Use**
- Open any Windows CLI (Command Prompt, PowerShell)
- Run 'jcalc \<expression>'
Example:
```
jcalc 3(2 + 3) - 4(3 * 4) / 42
3\
```

## **Build Instructions**
- Download and extract the zip folder from 'releases'
- Run the file named 'build.bat' with administrator privileges
- Navigate to Windows Advanced System Settings
- Click 'Environment Variables'
- Go to 'System Variables' and select 'PATH'
- Add 'C:\Program Files\jcalc'
