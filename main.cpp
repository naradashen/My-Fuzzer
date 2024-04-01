#include <iostream>
#include <vector>
#include <string>
#include <cstdlib> // For system() function
#include <fstream> // For file output
#include <thread> // For parallel requests
#include <mutex> // For thread safety
#include <unordered_set> // For storing unique URLs

// Global mutex for thread-safe output
std::mutex mtx;

// Function to perform directory and file enumeration (enhanced version)
void performEnumeration(const std::string& baseUrl, const std::vector<std::string>& dirFileNames, std::ofstream& outputFile, std::unordered_set<std::string>& foundUrls) {
    for (const auto& name : dirFileNames) {
        std::string url = baseUrl + "/" + name;
        std::string curlCommand = "curl -s -L -o /dev/null -w '%{http_code}' " + url;
        std::string curlOutput = "";
        FILE* curlStream = popen(curlCommand.c_str(), "r");
        if (curlStream) {
            char buffer[128];
            while (!feof(curlStream)) {
                if (fgets(buffer, sizeof(buffer), curlStream) != NULL) {
                    curlOutput += buffer;
                }
            }
            pclose(curlStream);

            // Check if the HTTP status code is 200 OK or 302 Found
            if (curlOutput.find("200") != std::string::npos || curlOutput.find("302") != std::string::npos) {
                mtx.lock(); // Lock mutex for thread-safe access to foundUrls
                if (foundUrls.find(url) == foundUrls.end()) { // Check if URL is not already found
                    outputFile << url << " - Found" << std::endl;
                    foundUrls.insert(url); // Add URL to foundUrls set
                }
                mtx.unlock(); // Unlock mutex
            }
        }
    }
}

int main() {
    std::string websiteUrl;
    std::vector<std::string> dirFileNames = {
        "admin", "backup", "login", "test", "wp-admin", "robots.txt", "sitemap.xml", "README.md",
        "images", "uploads", "css", "js", "fonts", "cgi-bin" , "bin" , "conf" , "data" , "db" , 
        "docs" , "downloads" , "include" , "js" , "lib" , "logs" , "media" , "modules" , 
        "mode-modules" , "phpmyadmin" , "script" , "src" , "temp" , "test" , "var" , "www" , 
        ".htaccess" , "LICENSE.txt" , "web.config" , "config.php" , "index.php" , "login.php" , 
        "admin.php" , "backup.sql" , "database.sql" , "report.pdf" , "credentials.txt" , "config.json", 
        "app.js" , "package.json" , "webpack.config.js", "Dockerfile" , "wp-login.php" , "phpinfo.php" , 
        "mysqladmin" , "dev" , "debug" , "backup" , "shell" , "logs" , "setup" , "phpMyAdmin" , 
        ".env" , ".git" , ".svn" , "config" , "confidential" , "dump" , "email" , "error" , "files" , 
        "ild_files" , "public" , "reports" , "temp" , "tmp" , "upload" , "web" , "admin.txt" , 
        "backup.zip" , "config.ini" , "credentials.json" , "db.sql" , "error_log" , "index.html" , 
        "info.php" , "login.html" , "passwords.txt" , "report.doc" , "setup.exe" , "shell.php" , 
        "test.php" , "usernames.txt" , "error" , "include" , "register" , "report" , "backup_files" , 
        "config_backup" , "development" , "devops" , "documents" , "important" , "invoices" , 
        "libraries" , "media" , "private" , "public_html" , "scripts" , "secure" , "sessions" , 
        "static" , "system" , "templates" , "tools" , "admin_panel.php" , "backup_db.sql" , 
        "config_backup.tar.gz" , "credentials_backup.txt" , "database_backup.sql" , "error_logs.log" ,
        "index.htm" , "password_list.txt" , "reports_backup.zip" , "setup.sh" , "shell_script.sh" ,
        "test_page.php" , "users_backup.csv" , ".config" , ".well-known" , "lib" , "public_html" , 
        "scripts" , "secure", "sessions" , "webroot" , ".idea" , ".vscode" , "admin_panel" , 
        "webapps" , "vti_bin/_vti_adm/admin.dll" , "vti_bin/_vti_adm/author.dll" , 
        "vti_bin/shtml.dll" , "vti_cnf" , "vti_inf" , "vti_log" , "vti_map" , "vti_pvt" , 
        "vti_rpc" , "vti_script" , "vti_txt" , "wp-app" , "wp-atom" , "wpau-backup" , "wp-blog-header" , 
        "wpcallback" , "wp-comments" , "wp-commentsrss2" , "wp-config" , "wpcontent" , "wp-content" , 
        "wp-cron" , "wp-dbmanager" , "wp-feed" , "wp-includes" , "wp-images" , "wp-mail" , "wp-pass" , 
        "wp-rdf" , "wp-register" , "wp-rss" , "wp-rss2" , "wps" , "wp-settings" , "wp-signup" , 
        "wp-syntax" , "wp-trackback" , "wrap" , "ws" , "ws_ftp" , "WS_FTP" , "WS_FTP.LOG" , 
        "ws-client" , "wsdl" , "wstat" , "wstats" , "wwwlog" , "wwwuser" , "xajax" , "xajax_js" , 
        "xcache" , "xcart" , "xhtml" , "xmfiles" , "xmlimporter" , "xmlrpc" , "xml-rpc" , 
        "xmlrpc.php" , "xmlrpc_server" , "xmlrpc_server.php" , "xmlrpc_server.php"


        // Add more common directory and file names as needed
    };
    std::unordered_set<std::string> foundUrls; // Set to store unique URLs

    std::cout << "Enter the target website URL to perform directory and file enumeration: ";
    std::getline(std::cin, websiteUrl);

    std::ofstream outputFile("enumeration_results.txt");
    if (!outputFile.is_open()) {
        std::cerr << "Error: Unable to open output file." << std::endl;
        return 1;
    }

    std::vector<std::thread> threads;
    for (int i = 0; i < 10; ++i) { // Adjust the number of threads as needed
        threads.emplace_back([&websiteUrl, &dirFileNames, &outputFile, &foundUrls]() {
            performEnumeration(websiteUrl, dirFileNames, outputFile, foundUrls);
        });
    }

    for (auto& thread : threads) {
        thread.join();
    }

    outputFile.close();
    std::cout << "Enumeration complete. Results saved to enumeration_results.txt." << std::endl;

    return 0;
}
