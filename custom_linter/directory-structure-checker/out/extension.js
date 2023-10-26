"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.activate = void 0;
const vscode = require("vscode");
const child_process_1 = require("child_process");
let diagnosticCollection;
function activate(context) {
    diagnosticCollection = vscode.languages.createDiagnosticCollection('YourLinterName');
    if (vscode.window.activeTextEditor) {
        lint(vscode.window.activeTextEditor.document);
    }
    // Listen to changes to lint in real-time
    context.subscriptions.push(vscode.workspace.onDidChangeTextDocument(event => {
        lint(event.document);
    }));
}
exports.activate = activate;
function lint(document) {
    if (document.uri.scheme !== 'file') {
        return;
    }
    // Run your custom linter
    const result = (0, child_process_1.execSync)(`python3 ../../linter.py ${document.fileName}`).toString().trim().split("\n");
    // Parse the results and create diagnostics
    const diagnostics = [];
    for (const issue of result) {
        const diagnostic = {
            severity: vscode.DiagnosticSeverity.Error,
            range: new vscode.Range(0, 0, 0, 0),
            message: issue,
            source: 'Directory Structure Checker'
        };
        diagnostics.push(diagnostic);
    }
    diagnosticCollection.set(document.uri, diagnostics);
}
//# sourceMappingURL=extension.js.map