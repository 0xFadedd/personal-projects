import * as vscode from "vscode";
import { execSync } from "child_process";

let diagnosticCollection: vscode.DiagnosticCollection;

export function activate(context: vscode.ExtensionContext) {
  diagnosticCollection =
    vscode.languages.createDiagnosticCollection("Directory Structure Checker");

  if (vscode.window.activeTextEditor) {
    lint(vscode.window.activeTextEditor.document);
  }

  // Listen to changes to lint in real-time
  context.subscriptions.push(
    vscode.workspace.onDidChangeTextDocument((event) => {
      console.log(event.document)
      lint(event.document);
    })
  );
}

function lint(document: vscode.TextDocument) {
  
  if (document.uri.scheme !== "file") {
    return;
  }

  vscode.window.showInformationMessage('Linting file: ' + document.fileName);

  let result: string[] = [];
  try {
    result = execSync(`python3 ./linter.py ${document.fileName}`)
      .toString()
      .trim()
      .split("\n");
  } catch (error : any) {
    vscode.window.showErrorMessage(`Failed to run linter: ${error.message}`);
    return;
  }
  console.log(result);

  // Parse the results and create diagnostics
  const diagnostics: vscode.Diagnostic[] = [];
  for (const issue of result) {
    const diagnostic: vscode.Diagnostic = {
      severity: vscode.DiagnosticSeverity.Error, // Changed to 'Error' to highlight the file name in red
      range: new vscode.Range(0, 0, 0, 0), // This highlights the first line. Adjust if you know the exact line of the error.
      message: issue,
      source: "Directory Structure Checker",
    };
    diagnostics.push(diagnostic);
  }

  diagnosticCollection.set(document.uri, diagnostics);
}
