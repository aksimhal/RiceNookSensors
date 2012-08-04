Imports System
Imports System.ComponentModel
Imports System.Threading
Imports System.Text
Imports System.IO.Ports


Module Module1
    Dim WithEvents comPort As SerialPort = My.Computer.Ports.OpenSerialPort("COM4", 9600, System.IO.Ports.Parity.None, 8, System.IO.Ports.StopBits.One)
    Dim buffer As New StringBuilder
    Sub Main()
        'Dim s As String = comPort.ReadExisting()
        'Console.WriteLine(s)
        While True
            Dim s As String = buffer.ToString()
            Console.WriteLine(s)
            buffer.Clear()
            Thread.Sleep(700)
        End While
    End Sub

    Private Sub comPort_DataReceived(ByVal sender As Object, ByVal e As System.IO.Ports.SerialDataReceivedEventArgs) Handles comPort.DataReceived
        buffer.AppendLine(comPort.ReadExisting())    'Automatically called every time a data is received at the serialPort
    End Sub

End Module
