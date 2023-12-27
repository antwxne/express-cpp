#include "ECsPressPapp.hpp"
#include "Network/HTTP.hpp"

int main()
{
    ecspressp::eCsPressPAPP<ecspressp::HTTP> app;

    app.Start();
    return 0;
}
