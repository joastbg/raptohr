#include "runner.h"

std::unordered_map<std::string, std::string> db;
std::unordered_map<std::string, double> sdb;
std::vector<std::string> snicodes;

//const char str[] =
//    "HTTP/1.1 200 OK\r\nDate: Mon, 5 Nov 2016 16:03:34 GMT\r\nContent-Type: application/json; charset=UTF-8\r\nContent-Encoding: UTF-8\r\nContent-Length: %d\r\nLast-Modified: Wed, 08 Jan 2003 23:11:55 GMT\r\nServer: Apache/1.3.3.7 (Unix) (Red-Hat/Linux)\r\nETag: \"3f80f-1b6-3e1cb03b\"\r\nAccept-Ranges: bytes\r\nConnection: close\r\n\r\n%s";

unsigned int req_seqnr = 0;


/* 
    JSON: https://tools.ietf.org/html/rfc7159
*/

std::ostream& operator<<(std::ostream& out, const DBTriple& dbt) {	
    out << std::boolalpha;
	out << "-- DBTriple :: " << dbt.spo() << std::endl;		
    return out;
}

void setnonblocking(int sock)
{
    int opts;
    opts = fcntl(sock, F_GETFL);
    if (opts < 0) {
	    perror("fcntl(sock,GETFL)");
	    exit(1);
    }
    opts = opts | O_NONBLOCK;
    if (fcntl(sock, F_SETFL, opts) < 0) {
	    perror("fcntl(sock,SETFL,opts)");
	    exit(1);
    }
}

void ssplit(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss;
    ss.str(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
}

std::vector<std::string> ssplit(const std::string &s, char delim) {
    std::vector<std::string> elems;
    ssplit(s, delim, elems);
    return elems;
}

void do_use_fd(int client_fd)
{
    char buffer[1024];
    char buf2[1024];
    int len;
    
    if ((len = read(client_fd, buffer, 1024)) == -1) {
	    perror("read");
    }
    
    buffer[len] = 0;
    
    //printf("#%d: Received:\n%s\n\n", ++req_seqnr, buffer);
    
    //---------------
    

    
    //---------------
    
    std::string s(buffer);
        
    std::vector<std::string> x = ssplit(s, '\n');

    /*
    for (std::string xs : x) {
        std::cout << xs << std::endl;
    }*/

    // Req path is first element x[0]
    

    //---------------    
        
    std::regex word_regex("(/[A-z0-9.]+)+");
    std::smatch sm;
    std::string path("/");
    
    
    if (x.size() > 0 && std::regex_search(x[0], sm, word_regex)) {
        //std::cout << "PATH: " << sm.str()  << std::endl;
        path = sm.str();
    }

    //---------------
    
    std::stringstream ss;

    if (path == "/company") {
        
        ss << "<div style='padding: 20px; width: 600px; border: 1px solid black; background: #cacaca; font-size: 1.5em; font-weight: 400; font-family: helvetica;'><a href='#'>A sample company...</a><br><br><tt>Orgnr...</tt></div><br><br>\n";
        
    } else if (path == "/") {
    
        ss << "<h1>Welcome!</h1>This is raptohr serving.\n";
    
    } else if (path == "/sha1") {
         
        crypto::SHA1 sha1;         
         
        ss << "<h1>Welcome!</h1><ul>\n";
         
        for (int i=0;i<50;i++) {
               
            std::srand(std::time(0) + i); 
            int randi = std::rand();
            
            std::stringstream sst;
            sst << randi;
            std::string digest(sst.str());
            sha1.update(digest);
            ss << "<li><tt>" << sha1.final() << "</tt></li>\n";
        }
        
        ss << "</ul>\n";
    
    } else if (path == "/about") {
    
        ss << "<h1>Raptohr</h1>Raptohr is a lighweight backend infrastructure.\n";
    
    } else if (path == "/surprise") {
    
        std::unordered_map<std::string, std::string>::iterator itr = db.begin();
        
        int random_number = std::experimental::randint(1, 10000);
    
        for (std::advance(itr, random_number); itr != db.end(); itr++) {
            ss << "<div style='margin: 100px; padding: 25px; width: 75%; border: 2px solid black; background: #dadada; font-size: 1.4em; font-weight: 400; font-family: helvetica;'>";            
            ss << "<h1 style='text-transform: uppercase'>" << (*itr).second << "</h1>";
            ss << "<tt><b>Orgnr</b>: " << (*itr).first << "</tt>";
            
            ss << "<br><br><ul style='list-style-type: none;'>";
            
            std::vector<std::string>::iterator itr1 = snicodes.begin();
            int random_number2 = std::experimental::randint(0, static_cast<int>(snicodes.size()));
            int random_number3 = std::experimental::randint(1, 5);
            unsigned int count1 = 0;
            
            if (snicodes.size() > 0) {
                for (std::advance(itr1, random_number2); count1++ < random_number3; itr1++) {
                    ss << "<li style='float: left; margin-right: 10px;'><a href='/snis'>#" << (*itr1) << "</a></li>";
                }
            }
            
            ss << "</ul>";            
            ss << "<br><br><h4>Similar Companies</h4><ul>";
                 
            std::unordered_map<std::string, std::string>::iterator itr2 = db.begin();
            unsigned int count = 0;
            
            for (itr2 = db.begin(); itr2 != db.end() && (++count < 10); itr2++) {
                ss << "<li><a href='/surprise' style='text-transform: uppercase'>" << (*itr2).second << "</a></li>\n";          
            }
                        
            ss << "</ul></div><br><br>\n";          
            break;
        }   
    
    } else if (path == "/snis") {
        
        std::vector<std::string>::iterator itr3;
        ss << "<h1>Swedish SNIs 2007</h1><br><ul>";

        for (itr3 = snicodes.begin(); itr3 != snicodes.end(); itr3++) {
            ss << "<li><a href='#'>" << (*itr3) << "</a></li>\n";           
        } 

        ss << "</ul>\n";
        
    } else if (path == "/companies") {
    
        std::unordered_map<std::string, std::string>::iterator itr = db.begin();
        unsigned int count = 0;
    
        for (itr = db.begin(); itr != db.end() && (++count < 50); itr++) {
            ss << "<div style='padding: 20px; width: 600px; border: 1px solid black; background: #cacaca; font-size: 1.5em; font-weight: 400; font-family: helvetica;'><a href='/surprise'>" << (*itr).second << "</a><br><br><tt>" << (*itr).first << "</tt></div><br><br>\n";          
        } 
          
    } else {
        ss << "<h1>404</h1>The requested page was not found.\n";
    }
    
    //---------------
       
    std::string str = ss.str();
    
    if (send(client_fd, str.c_str(), str.size(), 0) == -1) {
        perror("send");        
    }
    
    close(client_fd);
}


struct ci_less : std::binary_function<std::string, std::string, bool> {
    // case-independent (ci) compare_less binary function
    struct nocase_compare : public std::binary_function<unsigned char,unsigned char,bool> 
    {
      bool operator() (const unsigned char& c1, const unsigned char& c2) const {
          return tolower (c1) < tolower (c2); 
      }
    };
    bool operator() (const std::string & s1, const std::string & s2) const {
      return std::lexicographical_compare 
        (s1.begin (), s1.end (),   // source range
        s2.begin (), s2.end (),   // dest range
        nocase_compare ());  // comparison
    }
};

int lexicographical()
{
    std::string str[10], temp;

    std::cout << "Enter 10 words: " << std::endl;
    for(int i = 0; i < 10; ++i)
    {
      std::getline(std::cin, str[i]);
    }

    for(int i = 0; i < 9; ++i)
       for( int j = i+1; j < 10; ++j)
       {
          if(str[i] > str[j])
          {
            temp = str[i];
            str[i] = str[j];
            str[j] = temp;
          }
    }

    std::cout << "In lexicographical order: " << std::endl;

    for(int i = 0; i < 10; ++i)
    {
       std::cout << str[i] << std::endl;
    }
    return 0;
}

void Runner::run() {

    std::cout << std::endl << ANSI_COLOR_GREEN << ">> booting up...";
    std::cout << ANSI_COLOR_RESET << std::endl;

    // Check options
    if (!options.validate()) return;

    // Do testing (1)

    Complex<double> c1(1, 2);
    Complex<double> c2(1.03, -2.03);
    std::cout << c1;
    std::cout << c2;

    // ---
    
    sdb["1:1"] = 1.21;
    sdb["2:2"] = 1.22;
    sdb["3:3"] = 1.23;
    sdb["4:4"] = 1.24;
    sdb["5:5"] = 1.25;
    
    std::cout << "-- SparseHash :: " << sdb["1:1"] << std::endl;
    
    // ---

    //lexicographical();

    // ---
    
    if (1 == 0) { // disabled
        std::vector<int> range {1,2,3,4};
        do {
            std::copy(std::begin(range), std::end(range), std::ostream_iterator<int> {std::cout, " "});
            std::cout << std::endl;
        } while(std::next_permutation(std::begin(range), std::end(range)));
    }
    
    // ---
    
    // decimal to and from binary
    unsigned long input = 277;
    
    std::string binary = std::bitset<16>(277).to_string();
    std::cout << "-- Lib :: binary(" << input << ") = " << binary << std::endl;

    unsigned long decimal = std::bitset<16>(binary).to_ulong();
    std::cout << "-- Lib :: decimal(" << binary << ") = " << decimal << std::endl;

    // ---
    
    Matrix<double> m1;
    
    m1[0][0] = 3.14;
    
    std::cout << m1[0][0] << std::endl;
    std::cout << m1[1][0] << std::endl;
    
    m1.debug(std::cout);
    
    m1[1][0] = 3.15;
    
    std::cout << m1[0][0] << std::endl;
    std::cout << m1[1][0] << std::endl;
    
    m1.debug(std::cout);
    
    std::cout << "{rows: " << m1.rows << ", cols: " << m1.cols << "}" << std::endl;
    
    // ---
    
    std::vector<int> v1 {1,2,3,4,5,6,7,8,9,10};
    std::vector<int> v2 {11,12,13,14,15,16,17,18,19,20};
    
    // interleave (merge)
    std::vector<int> dst;
    std::merge(v1.begin(), v1.end(), v2.begin(), v2.end(), std::back_inserter(dst));
    
    std::cout << "-- Lib :: interleaved:" << std::endl << " ";
    std::copy(dst.begin(), dst.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << '\n';

    // ---

    unsigned short x = 0x0;
    unsigned short y = 0xFFFF;
    unsigned int z;

    z = MortonTable256[y >> 8]   << 17 | 
        MortonTable256[x >> 8]   << 16 |
        MortonTable256[y & 0xFF] <<  1 | 
        MortonTable256[x & 0xFF];

    std::cout << std::bitset<32>(z).to_string() << std::endl;

    // ---

    test_gray();
    
    // ---

    exit(0);

    // Do testing (2)
    DBTriple spo1("johan", "is-friend-of", "kalle");   
     
    std::cout << spo1.spo() << std::endl;
    std::cout << spo1.sop() << std::endl;
    std::cout << spo1.ops() << std::endl;
    std::cout << spo1.osp() << std::endl;
    std::cout << spo1.pso() << std::endl;
    std::cout << spo1.pos() << std::endl;
    
    DBTriple spo2("johan", "is-friend-of", "nisse");
    DBTriple spo3("johan", "is-friend-of", "pelle");
    DBTriple spo4("johan", "is-friend-of", "olle");
    
    DBTriple spo5("nisse", "is-friend-of", "johan");
    DBTriple spo6("pelle", "is-friend-of", "olle");

    std::map<std::string, std::vector<std::string>, ci_less> myMap;

    // ---
    
    std::cout << std::endl;
    std::cout << "-- Testing secondary index functionality..." << std::endl;
    
    myMap[spo1.spo()].push_back("1");
    myMap[spo2.spo()].push_back("2");
    myMap[spo3.spo()].push_back("3");
    myMap[spo4.spo()].push_back("4");    
    myMap[spo5.spo()].push_back("5");
    myMap[spo6.spo()].push_back("6");
    
    auto lb = myMap.lower_bound("spo:johan:is-friend-of:");
    auto ub = myMap.upper_bound("spo:johan:is-friend-of:zzzzzzzzzz");
        
    // print content:
    for (std::map<std::string, std::vector<std::string>, ci_less>::iterator it=lb; it!=ub; ++it) {
        std::cout << it->first << std::endl;
    }

    std::cout << "--" << std::endl;

    // ---
    
    //exit(0);

    // Load data
    std::string line;
    std::ifstream infile("test/testdata");

    while (std::getline(infile, line)) {
        
        std::vector<std::string> x = ssplit(line, '\t');
        db[x[0]] = x[1];
    }
    
    std::ifstream infile2("test/snicodes");

    while (std::getline(infile2, line)) {
        snicodes.push_back(line);
    }   
    
    // Start HTTP Facade
    memset(&serv, 0, sizeof(serv));
    serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = htonl(INADDR_ANY);
    serv.sin_port = htons(PORT);

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    socklen_t addrlen = 0;

    bind(sockfd, (struct sockaddr *) &serv, sizeof(struct sockaddr));
    listen(sockfd, 1);

    struct epoll_event ev, events[MAX_EVENTS];
    socklen_t listen_sock, conn_sock;
    int nfds, epollfd, n;

    epollfd = epoll_create1(0);
    if (epollfd == -1) {
        perror("epoll_create1");
        exit(EXIT_FAILURE);
    }
    
    listen_sock = sockfd;
    ev.events = EPOLLIN;
    ev.data.fd = listen_sock;
    
    if (epoll_ctl(epollfd, EPOLL_CTL_ADD, listen_sock, &ev) == -1) {
        perror("epoll_ctl: listen_sock");
        exit(EXIT_FAILURE);
    }

    for (;;) {
        
        nfds = epoll_wait(epollfd, events, MAX_EVENTS, -1);
        
        if (nfds == -1) {
            perror("epoll_wait");
            exit(EXIT_FAILURE);
        }
        
        for (n = 0; n < nfds; ++n) {
            if (events[n].data.fd == listen_sock) {
                
                conn_sock = accept(listen_sock, (struct sockaddr *) &addr, &addrlen);
                
                if (conn_sock == -1) {
                    perror("accept");
                    exit(EXIT_FAILURE);
                }
                
                setnonblocking(conn_sock);
                ev.events = EPOLLIN | EPOLLET;
                ev.data.fd = conn_sock;
                
                if (epoll_ctl(epollfd, EPOLL_CTL_ADD, conn_sock, &ev) == -1) {
                    perror("epoll_ctl: conn_sock");
                    exit(EXIT_FAILURE);
                }
                
            } else {
                do_use_fd(events[n].data.fd);
            }
       }
    }
}