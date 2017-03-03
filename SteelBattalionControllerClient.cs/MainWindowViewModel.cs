using Net;
using System;

namespace SteelBattalionControllerClient.cs
{
    class MainWindowViewModel : ViewModelBase, IDisposable
    {
        public SteelBattalionController Controller { get; set; }

        public MainWindowViewModel()
        {
            Controller = new SteelBattalionController();
        }

        public void Dispose()
        {
            if(Controller != null)
                Controller.Dispose();
        }
    }
}
