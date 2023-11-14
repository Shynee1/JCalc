# JCalc
Simple CLI tool to parse math expressions. \
Follows the order of operations / PEMDAS.

## **Documentation**
- Open any Windows CLI (Command Prompt, PowerShell)
- Run 'jcalc \<expression>'
```
jcalc "3(2 + 3) - 4(3 * 4) / 42"
```

## **Build Instructions**
- Download and extract the zip folder from 'releases'
- Run the file named 'build.bat' with administrator privileges
- Navigate to Windows Advanced System Settings
- Click 'Environment Variables'
- Go to 'System Variables' and select 'PATH'
- Add 'C:\Program Files\jcalc'

## **How It Works**
- Tokenizes string expression
- Creates AST using Pratt Parsing
- Evaluates AST to double

