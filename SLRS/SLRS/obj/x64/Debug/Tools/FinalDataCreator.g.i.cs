﻿#pragma checksum "..\..\..\..\Tools\FinalDataCreator.xaml" "{406ea660-64cf-4c82-b6f0-42d48172a799}" "1E8002DA09E12297E68F9E33D4182F25"
//------------------------------------------------------------------------------
// <auto-generated>
//     Dieser Code wurde von einem Tool generiert.
//     Laufzeitversion:4.0.30319.42000
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
    /// Tools
    /// </summary>
    public partial class Tools : System.Windows.Window, System.Windows.Markup.IComponentConnector {
        
        
        #line 6 "..\..\..\..\Tools\FinalDataCreator.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.Button btn_extract;
        
        #line default
        #line hidden
        
        
        #line 7 "..\..\..\..\Tools\FinalDataCreator.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.Button btn_globalData;
        
        #line default
        #line hidden
        
        
        #line 8 "..\..\..\..\Tools\FinalDataCreator.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.Button btn_sort;
        
        #line default
        #line hidden
        
        
        #line 9 "..\..\..\..\Tools\FinalDataCreator.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.Button btn_convert;
        
        #line default
        #line hidden
        
        
        #line 10 "..\..\..\..\Tools\FinalDataCreator.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.Button btn_multiplyData;
        
        #line default
        #line hidden
        
        
        #line 11 "..\..\..\..\Tools\FinalDataCreator.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.Button btn_createRDF;
        
        #line default
        #line hidden
        
        
        #line 12 "..\..\..\..\Tools\FinalDataCreator.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.Button btn_mergeImages;
        
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
            System.Uri resourceLocater = new System.Uri("/SLRS;component/tools/finaldatacreator.xaml", System.UriKind.Relative);
            
            #line 1 "..\..\..\..\Tools\FinalDataCreator.xaml"
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
            this.btn_extract = ((System.Windows.Controls.Button)(target));
            
            #line 6 "..\..\..\..\Tools\FinalDataCreator.xaml"
            this.btn_extract.Click += new System.Windows.RoutedEventHandler(this.extractTestData_Click);
            
            #line default
            #line hidden
            return;
            case 2:
            this.btn_globalData = ((System.Windows.Controls.Button)(target));
            
            #line 7 "..\..\..\..\Tools\FinalDataCreator.xaml"
            this.btn_globalData.Click += new System.Windows.RoutedEventHandler(this.extractSingleData_Click);
            
            #line default
            #line hidden
            return;
            case 3:
            this.btn_sort = ((System.Windows.Controls.Button)(target));
            
            #line 8 "..\..\..\..\Tools\FinalDataCreator.xaml"
            this.btn_sort.Click += new System.Windows.RoutedEventHandler(this.sortData_Click);
            
            #line default
            #line hidden
            return;
            case 4:
            this.btn_convert = ((System.Windows.Controls.Button)(target));
            
            #line 9 "..\..\..\..\Tools\FinalDataCreator.xaml"
            this.btn_convert.Click += new System.Windows.RoutedEventHandler(this.convertToFinalData_Click);
            
            #line default
            #line hidden
            return;
            case 5:
            this.btn_multiplyData = ((System.Windows.Controls.Button)(target));
            
            #line 10 "..\..\..\..\Tools\FinalDataCreator.xaml"
            this.btn_multiplyData.Click += new System.Windows.RoutedEventHandler(this.multiplyData_Click);
            
            #line default
            #line hidden
            return;
            case 6:
            this.btn_createRDF = ((System.Windows.Controls.Button)(target));
            
            #line 11 "..\..\..\..\Tools\FinalDataCreator.xaml"
            this.btn_createRDF.Click += new System.Windows.RoutedEventHandler(this.createRDFData_Click);
            
            #line default
            #line hidden
            return;
            case 7:
            this.btn_mergeImages = ((System.Windows.Controls.Button)(target));
            
            #line 12 "..\..\..\..\Tools\FinalDataCreator.xaml"
            this.btn_mergeImages.Click += new System.Windows.RoutedEventHandler(this.mergeImages_Click);
            
            #line default
            #line hidden
            return;
            }
            this._contentLoaded = true;
        }
    }
}

