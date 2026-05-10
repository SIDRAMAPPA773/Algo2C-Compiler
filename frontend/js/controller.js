document.addEventListener('DOMContentLoaded', () => {
    const editor = new EditorManager();
    const ui = new UIManager();

    document.getElementById('btn-compile').addEventListener('click', async () => {
        const code = editor.getCode();
        ui.consoleOut.innerHTML = '<span class="info-text">Compiling...</span>';
        
        // Button animation
        gsap.to('#btn-compile', {scale: 0.95, duration: 0.1, yoyo: true, repeat: 1});

        const result = await CompilerAPI.compile(code);
        
        ui.updateConsole(result.stdout, result.stderr, result.error);
        ui.updateGeneratedCode(result.c_code);
    });

    document.getElementById('btn-reset').addEventListener('click', () => {
        editor.setCode('START\n\nEND');
        ui.updateConsole('', '', null);
        ui.updateGeneratedCode('');
        ui.updateTokens([]);
        ui.updateSymbols([]);
    });

    document.getElementById('btn-copy').addEventListener('click', () => {
        const code = document.getElementById('generated-code').textContent;
        navigator.clipboard.writeText(code).then(() => {
            alert("Code copied to clipboard!");
        });
    });

    document.getElementById('btn-download').addEventListener('click', () => {
        const code = document.getElementById('generated-code').textContent;
        if (!code || code.includes('No C code generated')) {
            alert('No valid C code to download!');
            return;
        }
        const blob = new Blob([code], { type: 'text/plain' });
        const url = window.URL.createObjectURL(blob);
        const a = document.createElement('a');
        a.href = url;
        a.download = 'output.c';
        document.body.appendChild(a);
        a.click();
        document.body.removeChild(a);
        window.URL.revokeObjectURL(url);
    });
});
