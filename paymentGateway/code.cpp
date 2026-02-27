#include<bits/stdc++.h>
using namespace std;

class PaymentRequest{
    public:
        string sender;
        string receiver;
        double amount;
        string currency;
        PaymentRequest(string sender, string receiver, double amount, string currency){
            this->sender = sender;
            this->receiver = receiver;
            this->amount = amount;
            this->currency = currency;
        }
};

class BankingSystem{
    public:
        virtual bool makePayment(PaymentRequest request) = 0;
};

class Paytm : public BankingSystem{
    public:
        bool makePayment(PaymentRequest request){
            cout << "Processing payment through Paytm..." << endl;
            cout << "Sender: " << request.sender << endl;
            cout << "Receiver: " << request.receiver << endl;
            cout << "Amount: " << request.amount << " " << request.currency << endl;
            int r = rand() % 100;
            return r > 80;
        }
};

class Razorpay : public BankingSystem{
    public:
        bool makePayment(PaymentRequest request){
            cout << "Processing payment through Razorpay..." << endl;
            cout << "Sender: " << request.sender << endl;
            cout << "Receiver: " << request.receiver << endl;
            cout << "Amount: " << request.amount << " " << request.currency << endl;
            int r = rand() % 100;
            return r > 90;
        }
};

class PaymentGateway{
    public:
        BankingSystem* bankingSystem;
        PaymentGateway(){
            this->bankingSystem = nullptr;
        }
        bool processPayment(PaymentRequest request){
            if(!validatePayment(request)){
                cout << "Payment validation failed." << endl;
                return false;
            }
            if(!initiatePayment(request)){
                cout << "Payment initiation failed." << endl;
                return false;
            }
            if(!confirmPayment(request)){
                cout << "Payment confirmation failed." << endl;
                return false;
            }
            return true;
        }

        virtual bool validatePayment(PaymentRequest request) = 0;
        virtual bool initiatePayment(PaymentRequest request) = 0;
        virtual bool confirmPayment(PaymentRequest request) = 0;
};

class PaytmPaymentGateway : public PaymentGateway{
    public:
        PaytmPaymentGateway(){
            bankingSystem = new Paytm();
        }
        bool validatePayment(PaymentRequest request){
            if(request.amount <= 0){
                cout << "Invalid amount." << endl;
                return false;
            }
            if(request.currency != "INR"){
                cout << "Unsupported currency." << endl;
                return false;
            }
            return true;
        }
        bool initiatePayment(PaymentRequest request){
            cout << "Initiating payment through Paytm..." << endl;
            return bankingSystem->makePayment(request);
        }
        bool confirmPayment(PaymentRequest request){
            cout << "Confirming payment through Paytm..." << endl;
            return true;
        }
};

class RazorpayPaymentGateway : public PaymentGateway{
    public:
        RazorpayPaymentGateway(){
            bankingSystem = new Razorpay();
        }
        bool validatePayment(PaymentRequest request){
            if(request.amount <= 0){
                cout << "Invalid amount." << endl;
                return false;
            }
            
            return true;
        }
        bool initiatePayment(PaymentRequest request){
            cout << "Initiating payment through Razorpay..." << endl;
            return bankingSystem->makePayment(request);
        }
        bool confirmPayment(PaymentRequest request){
            cout << "Confirming payment through Razorpay..." << endl;
            return true;
        }
};

class PaymentGatewayProxy : public PaymentGateway{
    public:
        PaymentGateway* realGateway;
        int paymentAttempts;
        
        PaymentGatewayProxy(PaymentGateway* gateway, int attempts = 3){
            this->realGateway = gateway;
            this->paymentAttempts = attempts;
        }

        bool processPayment(PaymentRequest request){
            for(int i = 0; i < paymentAttempts; i++){
                cout << "Attempt " << (i + 1) << " of " << paymentAttempts << endl;
                if(realGateway->processPayment(request)){
                    cout << "Payment successful on attempt " << (i + 1) << "." << endl;
                    return true;
                }
                cout << "Payment failed on attempt " << (i + 1) << "." << endl;
            }
            cout << "All payment attempts failed." << endl;
            return false;
        }
        bool validatePayment(PaymentRequest request){
            return realGateway->validatePayment(request);
        }
        bool initiatePayment(PaymentRequest request){
            return realGateway->initiatePayment(request);
        }
        bool confirmPayment(PaymentRequest request){
            return realGateway->confirmPayment(request);
        }
};

enum class GatewayType{
    PAYTM,
    RAZORPAY
};

class GatewayFactory{
    private:
        static GatewayFactory* instance;
        GatewayFactory() {}
    public:
        static GatewayFactory* getInstance(){
            if(instance == nullptr){
                instance = new GatewayFactory();
            }
            return instance;
        }
        PaymentGateway* createGateway(GatewayType type){
            switch(type){
                case GatewayType::PAYTM:
                    return new PaymentGatewayProxy(new PaytmPaymentGateway(),3);
                case GatewayType::RAZORPAY:
                    return new PaymentGatewayProxy(new RazorpayPaymentGateway(),1);
                default:
                    return nullptr;
            }
        }
};

GatewayFactory* GatewayFactory::instance = nullptr;

class PaymentService{
    private:
        static PaymentService* instance;
        PaymentService() {}
    public:
        static PaymentService* getInstance(){
            if(instance == nullptr){
                instance = new PaymentService();
            }
            return instance;
        }
        PaymentGateway* gateway;

        void setGateway(PaymentGateway* gateway){
            this->gateway = gateway;
        }
        
        bool makePayment(PaymentRequest request){
            return gateway->processPayment(request);
        }
};

PaymentService* PaymentService::instance = nullptr;

class PaymentController{
    private:
    static PaymentController* instance;
    PaymentController() {}
    public:
    static PaymentController* getInstance(){
        if(instance == nullptr){
            instance =new PaymentController();
        }
        return instance;
    }
    void handlePaymentRequest(PaymentRequest request, GatewayType type){
        GatewayFactory* factory = GatewayFactory::getInstance();
        PaymentGateway* gateway = factory->createGateway(type);
        PaymentService* service = PaymentService::getInstance();
        service->setGateway(gateway);
        if(service->makePayment(request)){
            cout << "Payment processed successfully." << endl;
        } else {
            cout << "Payment processing failed." << endl;
        }
    }
};

PaymentController* PaymentController::instance = nullptr;

int main(){
    PaymentController* controller = PaymentController::getInstance();
    PaymentRequest request("Alice", "Bob", 1000, "INR");
    controller->handlePaymentRequest(request, GatewayType::PAYTM);
    return 0;
}