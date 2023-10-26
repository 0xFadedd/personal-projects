import * as vscode from "vscode";
import { execSync } from "child_process";

let diagnosticCollection: vscode.DiagnosticCollection;

export function activate(context: vscode.ExtensionContext) {
  diagnosticCollection = vscode.languages.createDiagnosticCollection(
    "Directory Structure Checker"
  );

  if (vscode.window.activeTextEditor) {
    lint(vscode.window.activeTextEditor.document, context);
  }

  context.subscriptions.push(
    vscode.workspace.onDidChangeTextDocument((event) => {
      lint(event.document, context);
    })
  );
}

function lint(document: vscode.TextDocument, context: vscode.ExtensionContext) {
  if (document.uri.scheme !== "file") {
    return;
  }
  console.log("Linting file: " + document.fileName)
  vscode.window.showInformationMessage("Linting file: " + document.fileName);

  let result: string[] = [];
  const linterPath = context.asAbsolutePath("./linter.py");
  result = execSync(`python3 "${linterPath}" "${document.fileName}"`)
    .toString()
    .trim()
    .split("\n");

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
    console.log(issue);
  }

  diagnosticCollection.set(document.uri, diagnostics);
}
