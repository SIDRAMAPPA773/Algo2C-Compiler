class EditorManager {
    constructor() {
        this.editor = CodeMirror.fromTextArea(document.getElementById("code-editor"), {
            lineNumbers: true,
            mode: "javascript", // Using JS mode for pseudo-code basic highlighting
            theme: "dracula",
            indentUnit: 4,
            matchBrackets: true,
            autoCloseBrackets: true
        });
    }

    getCode() {
        return this.editor.getValue();
    }

    setCode(code) {
        this.editor.setValue(code);
    }
}
