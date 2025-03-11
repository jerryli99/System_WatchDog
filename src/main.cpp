#include <QApplication>
#include "GUI/MainWindow/MainWindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv); // Create the QApplication object

    MainWindow mainWindow;        // Create the main window
    mainWindow.show();            // Show the main window

    return app.exec();            // Start the event loop
}

// #include <iostream>
// #include <pcap.h>

// int main() {
//     char errbuf[PCAP_ERRBUF_SIZE];
//     pcap_if_t *alldevs;

//     // Find all network devices
//     if (pcap_findalldevs(&alldevs, errbuf) == -1) {
//         std::cerr << "Error finding devices: " << errbuf << std::endl;
//         return 1;
//     }

//     // Print the list of devices
//     for (pcap_if_t *d = alldevs; d != nullptr; d = d->next) {
//         std::cout << "Device: " << d->name << std::endl;
//         if (d->description) {
//             std::cout << "  Description: " << d->description << std::endl;
//         }
//     }

//     // Free the device list
//     pcap_freealldevs(alldevs);

//     return 0;
// }
