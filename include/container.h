
class Container {
    private:
        Lan *lan;
    public:
        Container(Lan *lan): lan(lan) {}

        Lan* getLan() {
            return lan;
        }
};