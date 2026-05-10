class CompilerAPI {
    static async compile(code) {
        try {
            const response = await fetch('/api/compile', {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json'
                },
                body: JSON.stringify({ code })
            });
            return await response.json();
        } catch (error) {
            console.error("Compilation API Error:", error);
            return { error: error.message };
        }
    }
}
