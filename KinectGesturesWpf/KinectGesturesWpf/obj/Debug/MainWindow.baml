   M S B A M L   `   `   `  ����L  HKinectGesturesWpf, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null5clr-namespace:KinectGesturesWpfKinectGesturesWpf  5   	   "    KinectGesturesWpf.MainWindow   5   	   \ XPresentationFramework, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35R NWindowsBase, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35W SPresentationCore, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35D 9http://schemas.microsoft.com/winfx/2006/xaml/presentation    5   	   R NSystem.Xaml, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089:x,http://schemas.microsoft.com/winfx/2006/xaml     5   	   1localclr-namespace:KinectGesturesWpf     5   	   -   5          � Title$  KinectGesturesWpf��5   	   $
��1562��5   &   $	��700��63    � 	Resources 5         MediumGreyBrush �� Color  KinectPurpleBrush  KinectBlueBrush �� 
TargetType �� Property �� Value,   &KinectGesturesWpf.EnumBooleanConverter  enumConverter��%  &	        &	 #     &	 F     '�� i     &	 �     �� 5   
   $ 	#ff6e6e6e��62   �� 5	   
   $ 	#ff52318f��64   �� 5
   
   $ 	#ff00BCF2��62   �� 5   
   " ��6   .�5      ��  �@J�SnapsToDevicePixels . 64   5        5   
   6%   5      .��5      � $��10q�6    � ColumnDefinitions 5   
   �� 5      $
��1152 �6   �� 5      $	��400 �6    � RowDefinitions 5   
   �� 5      $	��648 �6   .+�5   
   (� $��0��6   $��0��6   $	��648��6/   $
��1152��6<   .��5      �� $��UniformToFill=�63   ��6   �� *ImageSource+63   5      �� 5   
   $
��Data��6   $��10,10,40,419q�6!   $��1��67   �� 5   
   -   5         ��Name$ 	txtAngles��5   1   $��0��6   $��1��6!   $��14(�6D   	 �� Padding$	 10q�6R   $��20,20,45,419q�6_   �� 5      $	�...��6   5      �� 5!   
   $��Success Rate��6   $��10,252,40,267q�6)   $��1��6@   �� 5"   
   -   5        $��txtSuccessRate��5"      $��-��6*   $
��Bold"�63   $	��300��6E   $��1��6Q   $��20,273,80,271q�6a   �� 5$   
   $
��25px(�6/   $
��Bold"�6?   $��1��6Q   $��10,559,28,10q�6a   ��6   �� *
StatusText+6a   �� 5%   
   $
��Bold"�60   $	��300��6B   $��25��6N   $��1��6Z   $��32,387,68,237q�6j   ��6   �� *GestureText+6j   �� 5'   
   $
��Mode��6   $��10,450,220,111q�6!   $��1��69   �� 5(   
   -   5        $��
chk_Record��5(      $��32,474,239,145q�6%   $��Record Mode��6=   $��30��6�   $��1��6�   �� 5)   
   -   5        $��chk_Classify��5)      $��32,508,239,111q�6'   $��Classification Mode��6?   $��30��6�   $��1��6�   �� 5+   
   $��Classification Type��6   $��202,450,28,111q�60   $��1��6H   	� 5,   
   $��Distance NN��6   $
��Left=�6�   $��219,472,0,147q�6�   $��1��6�   
 d� 	IsChecked
 6,   ��  �� Path$
 Type� �� 	Converter# [ +   %KinectGesturesWpf.ClassificationTypes   
DistanceNN �� ConverterParameter# Z 6�   	� 5-   
   $��Orientation NN��6   $
��Left=�6�   $��219,493,0,140q�6�   $��1��6�   
 6/   �� $
 Type�# [    OrientationNN# Z 6�   	� 5.   
   $��Orientation Bayes��6   $
��Left=�6�   $��219,515,0,111q�6�   $��1��6�   
 62   �� $
 Type�# [    OrientationBayes# Z 6�   51      52      