#include "Network/HTTP.hpp"
#include "Queue/QueueImplem.hpp"

int main()
{
    ecspressp::HTTP app;
    ecspressp::QueueImplem<ecspressp::HTTPRequest> input_queue;
    ecspressp::QueueImplem<ecspressp::HTTPResponse> output_queue;
    app.Start(input_queue, output_queue);

    return 0;
}
