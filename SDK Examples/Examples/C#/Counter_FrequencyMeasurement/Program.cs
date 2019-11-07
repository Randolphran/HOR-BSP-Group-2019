using System;
using System.Collections.Generic;
using System.Windows.Forms;

namespace Counter_FrequencyMeasurement
{
    static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new FrequencyMeasurementForm());
            //Application.Run(new FrequencyMeasure(7,7));
        }
    }
}