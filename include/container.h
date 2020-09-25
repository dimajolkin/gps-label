
class Container {
    private:
        Lan *lan;
        Server *server;
    public:
        Container(Lan *lan, Server *server): lan(lan), server(server) {}

        Lan* getLan() {
            return lan;
        }

        Server* getServer() {
            return server;
        }
};