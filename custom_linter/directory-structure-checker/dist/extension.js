(()=>{"use strict";var e={496:e=>{e.exports=require("vscode")},81:e=>{e.exports=require("child_process")}},t={};function o(r){var i=t[r];if(void 0!==i)return i.exports;var n=t[r]={exports:{}};return e[r](n,n.exports,o),n.exports}var r={};(()=>{var e=r;Object.defineProperty(e,"__esModule",{value:!0}),e.activate=void 0;const t=o(496),i=o(81);let n;function s(e,o){if("file"!==e.uri.scheme)return;console.log("Linting file: "+e.fileName),t.window.showInformationMessage("Linting file: "+e.fileName);let r=[];const s=o.asAbsolutePath("./linter.py");r=(0,i.execSync)(`python3 "${s}" "${e.fileName}"`).toString().trim().split("\n"),console.log(r);const c=[];for(const e of r){const o={severity:t.DiagnosticSeverity.Error,range:new t.Range(0,0,0,0),message:e,source:"Directory Structure Checker"};c.push(o),console.log(e)}n.set(e.uri,c)}e.activate=function(e){n=t.languages.createDiagnosticCollection("Directory Structure Checker"),t.window.activeTextEditor&&s(t.window.activeTextEditor.document,e),e.subscriptions.push(t.workspace.onDidChangeTextDocument((t=>{s(t.document,e)})))}})(),module.exports=r})();