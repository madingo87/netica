﻿#pragma checksum "..\..\EvaluationWindow - Kopieren.xaml" "{406ea660-64cf-4c82-b6f0-42d48172a799}" "C387CD3CECE4CCF9DCBA43DE67E284A5"
//------------------------------------------------------------------------------
// <auto-generated>
//     Dieser Code wurde von einem Tool generiert.
//     Laufzeitversion:4.0.30319.34209
//
//     Änderungen an dieser Datei können falsches Verhalten verursachen und gehen verloren, wenn
//     der Code erneut generiert wird.
// </auto-generated>
//------------------------------------------------------------------------------

using System;
using System.Diagnostics;
using System.Windows;
using System.Windows.Automation;
using System.Windows.Controls;
using System.Windows.Controls.Primitives;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Ink;
using System.Windows.Input;
using System.Windows.Markup;
using System.Windows.Media;
using System.Windows.Media.Animation;
using System.Windows.Media.Effects;
using System.Windows.Media.Imaging;
using System.Windows.Media.Media3D;
using System.Windows.Media.TextFormatting;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Windows.Shell;


namespace SLRS {
    
    
    /// <summary>
    /// EvaluationWindow
    /// </summary>
    public partial class EvaluationWindow : System.Windows.Window, System.Windows.Markup.IComponentConnector {
        
        
        #line 7 "..\..\EvaluationWindow - Kopieren.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.Button btn_selectMappingFile;
        
        #line default
        #line hidden
        
        
        #line 8 "..\..\EvaluationWindow - Kopieren.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.Label lbl_output;
        
        #line default
        #line hidden
        
        
        #line 9 "..\..\EvaluationWindow - Kopieren.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.Label lbl_mapping;
        
        #line default
        #line hidden
        
        
        #line 11 "..\..\EvaluationWindow - Kopieren.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.RichTextBox box_eval;
        
        #line default
        #line hidden
        
        
        #line 12 "..\..\EvaluationWindow - Kopieren.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.Button btn_writeMappings;
        
        #line default
        #line hidden
        
        
        #line 13 "..\..\EvaluationWindow - Kopieren.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.TextBox mappingsCount;
        
        #line default
        #line hidden
        
        private bool _contentLoaded;
        
        /// <summary>
        /// InitializeComponent
        /// </summary>
        [System.Diagnostics.DebuggerNonUserCodeAttribute()]
        [System.CodeDom.Compiler.GeneratedCodeAttribute("PresentationBuildTasks", "4.0.0.0")]
        public void InitializeComponent() {
            if (_contentLoaded) {
                return;
            }
            _contentLoaded = true;
            System.Uri resourceLocater = new System.Uri("/SLRS;component/evaluationwindow%20-%20kopieren.xaml", System.UriKind.Relative);
            
            #line 1 "..\..\EvaluationWindow - Kopieren.xaml"
            System.Windows.Application.LoadComponent(this, resourceLocater);
            
            #line default
            #line hidden
        }
        
        [System.Diagnostics.DebuggerNonUserCodeAttribute()]
        [System.CodeDom.Compiler.GeneratedCodeAttribute("PresentationBuildTasks", "4.0.0.0")]
        [System.ComponentModel.EditorBrowsableAttribute(System.ComponentModel.EditorBrowsableState.Never)]
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Design", "CA1033:InterfaceMethodsShouldBeCallableByChildTypes")]
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Maintainability", "CA1502:AvoidExcessiveComplexity")]
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1800:DoNotCastUnnecessarily")]
        void System.Windows.Markup.IComponentConnector.Connect(int connectionId, object target) {
            switch (connectionId)
            {
            case 1:
            
            #line 6 "..\..\EvaluationWindow - Kopieren.xaml"
            ((System.Windows.Controls.Button)(target)).Click += new System.Windows.RoutedEventHandler(this.btn_select_output_click);
            
            #line default
            #line hidden
            return;
            case 2:
            this.btn_selectMappingFile = ((System.Windows.Controls.Button)(target));
            
            #line 7 "..\..\EvaluationWindow - Kopieren.xaml"
            this.btn_selectMappingFile.Click += new System.Windows.RoutedEventHandler(this.btn_select_mapping_click);
            
            #line default
            #line hidden
            return;
            case 3:
            this.lbl_output = ((System.Windows.Controls.Label)(target));
            return;
            case 4:
            this.lbl_mapping = ((System.Windows.Controls.Label)(target));
            return;
            case 5:
            
            #line 10 "..\..\EvaluationWindow - Kopieren.xaml"
            ((System.Windows.Controls.Button)(target)).Click += new System.Windows.RoutedEventHandler(this.btn_eval_click);
            
            #line default
            #line hidden
            return;
            case 6:
            this.box_eval = ((System.Windows.Controls.RichTextBox)(target));
            return;
            case 7:
            this.btn_writeMappings = ((System.Windows.Controls.Button)(target));
            
            #line 12 "..\..\EvaluationWindow - Kopieren.xaml"
            this.btn_writeMappings.Click += new System.Windows.RoutedEventHandler(this.btn_write_mappings_click);
            
            #line default
            #line hidden
            return;
            case 8:
            this.mappingsCount = ((System.Windows.Controls.TextBox)(target));
            return;
            }
            this._contentLoaded = true;
        }
    }
}
