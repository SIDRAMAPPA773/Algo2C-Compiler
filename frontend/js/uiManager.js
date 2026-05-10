class UIManager {
    constructor() {
        this.consoleOut = document.getElementById('console-output');
        this.codeViewer = document.getElementById('generated-code');
        this.tokenTbody = document.getElementById('token-tbody');
        this.symbolTbody = document.getElementById('symbol-tbody');
        
        this.setupTabs();
    }

    setupTabs() {
        const tabs = document.querySelectorAll('.tab-btn');
        tabs.forEach(tab => {
            tab.addEventListener('click', () => {
                tabs.forEach(t => {
                    t.classList.remove('active', 'text-cyan-400', 'border-b-2', 'border-cyan-400');
                    t.classList.add('text-gray-400');
                });
                document.querySelectorAll('.tab-content').forEach(c => c.classList.remove('active', 'hidden'));
                document.querySelectorAll('.tab-content').forEach(c => c.classList.add('hidden'));
                
                tab.classList.add('active', 'text-cyan-400', 'border-b-2', 'border-cyan-400');
                tab.classList.remove('text-gray-400');
                
                const target = document.getElementById(tab.getAttribute('data-target'));
                target.classList.remove('hidden');
                // slight delay for animation
                setTimeout(() => target.classList.add('active'), 10);
            });
        });
    }

    updateConsole(stdout, stderr, error) {
        this.consoleOut.innerHTML = '';
        
        if (error) {
            this.appendConsole(`<span class="error-text">System Error: ${error}</span>`);
        }
        
        const output = stdout || '';
        const lines = output.split('\n');
        
        let tokens = [];
        let symbols = [];
        let consoleLines = [];
        
        lines.forEach(line => {
            if (line.startsWith('TOKEN:')) {
                try {
                    const tokenJson = JSON.parse(line.substring(6).trim());
                    tokens.push(tokenJson);
                } catch(e) {}
            } else if (line.startsWith('SYMBOL:')) {
                // e.g. SYMBOL: Declared a of type int at line 2
                const parts = line.split(' ');
                if (parts.length >= 8) {
                    symbols.push({
                        name: parts[2],
                        type: parts[5],
                        line: parts[8]
                    });
                }
                consoleLines.push(`<span class="info-text">${line}</span>`);
            } else if (line.includes('ERROR:') || line.includes('Error')) {
                consoleLines.push(`<span class="error-text">${line}</span>`);
            } else if (line.includes('INFO:') || line.includes('Successfully')) {
                consoleLines.push(`<span class="success-text">${line}</span>`);
            } else if (line.trim() !== '') {
                consoleLines.push(line);
            }
        });

        if (stderr) {
            consoleLines.push(`<span class="error-text">${stderr}</span>`);
        }

        this.consoleOut.innerHTML += consoleLines.join('\n');
        this.updateTokens(tokens);
        this.updateSymbols(symbols);
        
        // GSAP Animation for console
        gsap.fromTo(this.consoleOut, {opacity: 0, y: 10}, {opacity: 1, y: 0, duration: 0.3});
    }

    appendConsole(htmlLine) {
        this.consoleOut.innerHTML += htmlLine + '<br>';
    }

    updateTokens(tokens) {
        this.tokenTbody.innerHTML = '';
        tokens.forEach((t, i) => {
            const tr = document.createElement('tr');
            tr.className = 'border-b border-gray-800 hover:bg-gray-800/50 transition-colors';
            tr.innerHTML = `
                <td class="px-4 py-2">${t.line}</td>
                <td class="px-4 py-2 text-cyan-300">${t.lexeme}</td>
                <td class="px-4 py-2 text-purple-400">${t.type}</td>
            `;
            this.tokenTbody.appendChild(tr);
            
            // Stagger animation
            gsap.fromTo(tr, {opacity: 0, x: -10}, {opacity: 1, x: 0, duration: 0.2, delay: i * 0.01});
        });
    }

    updateSymbols(symbols) {
        this.symbolTbody.innerHTML = '';
        symbols.forEach((s, i) => {
            const tr = document.createElement('tr');
            tr.className = 'border-b border-gray-800 hover:bg-gray-800/50 transition-colors';
            tr.innerHTML = `
                <td class="px-4 py-2 text-yellow-300">${s.name}</td>
                <td class="px-4 py-2 text-blue-400">${s.type}</td>
                <td class="px-4 py-2">${s.line}</td>
            `;
            this.symbolTbody.appendChild(tr);
            
            // Stagger animation
            gsap.fromTo(tr, {opacity: 0, x: -10}, {opacity: 1, x: 0, duration: 0.2, delay: i * 0.02});
        });
    }

    updateGeneratedCode(code) {
        this.codeViewer.textContent = code || '/* No C code generated. Check for compilation errors. */';
        Prism.highlightElement(this.codeViewer);
        
        if (code) {
            gsap.fromTo(this.codeViewer.parentElement, {opacity: 0, scale: 0.98}, {opacity: 1, scale: 1, duration: 0.4});
        }
    }
}
