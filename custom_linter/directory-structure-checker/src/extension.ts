import * as vscode from 'vscode';
import { execSync } from 'child_process';

let diagnosticCollection: vscode.DiagnosticCollection;

export function activate(context: vscode.ExtensionContext) {
    diagnosticCollection = vscode.languages.createDiagnosticCollection('YourLinterName');
    
    if (vscode.window.activeTextEditor) {
        lint(vscode.window.activeTextEditor.document);
    }

    // Listen to changes to lint in real-time
    context.subscriptions.push(vscode.workspace.onDidChangeTextDocument(event => {
        lint(event.document);
    }));
}

function lint(document: vscode.TextDocument) {
    if (document.uri.scheme !== 'file') {
        return;
    }

    // Run your custom linter
    const result = execSync(`python3 path_to_your_linter/linter.py ${document.fileName}`).toString().trim().split("\n");
    
    // Parse the results and create diagnostics
    const diagnostics: vscode.Diagnostic[] = [];
    for (const issue of result) {
        const diagnostic: vscode.Diagnostic = {
            severity: vscode.DiagnosticSeverity.Warning,
            range: new vscode.Range(0, 0, 0, 0),
            message: issue,
            source: 'YourLinterName'
        };
        diagnostics.push(diagnostic);
    }

    diagnosticCollection.set(document.uri, diagnostics);
}
