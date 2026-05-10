const express = require('express');
const bodyParser = require('body-parser');
const { exec } = require('child_process');
const fs = require('fs');
const path = require('path');

const app = express();
app.use(bodyParser.json());
app.use(express.static(path.join(__dirname, 'frontend')));

app.get('/', (req, res) => {
    res.sendFile(path.join(__dirname, 'frontend', 'views', 'index.html'));
});

app.post('/api/compile', (req, res) => {
    const code = req.body.code;
    const inputFilePath = path.join(__dirname, 'input.txt');
    fs.writeFileSync(inputFilePath, code);

    const compilerPathWin = path.join(__dirname, 'backend', 'compiler.exe');
    const compilerPathLin = path.join(__dirname, 'backend', 'compiler');
    let finalCompiler = '';
    
    if (fs.existsSync(compilerPathWin)) finalCompiler = compilerPathWin;
    else if (fs.existsSync(compilerPathLin)) finalCompiler = compilerPathLin;
    else {
        return res.status(500).json({ error: 'Compiler executable not found. Please build the backend first using Make. The system MUST NOT use fake simulations per your strict requirements.' });
    }

    const command = `"${finalCompiler}" "${inputFilePath}"`;
    
    exec(command, { cwd: path.join(__dirname, 'backend') }, (error, stdout, stderr) => {
        let c_code = '';
        const outputFilePath = path.join(__dirname, 'backend', 'output.c');
        if (fs.existsSync(outputFilePath)) {
            c_code = fs.readFileSync(outputFilePath, 'utf8');
        }

        res.json({
            stdout: stdout,
            stderr: stderr,
            c_code: c_code,
            error: error ? error.message : null
        });
    });
});

const PORT = 3000;
app.listen(PORT, () => {
    console.log(`Algo2C-Compiler IDE running at http://localhost:${PORT}`);
});
