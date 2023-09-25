using BacktestGrpc.Protos;
using Grpc.Core;
using GrpcBacktestServer;

namespace GrpcBacktestServer.Services
{
    public class BacktestRunnerService : BacktestRunner.BacktestRunnerBase
    {
        private readonly ILogger<BacktestRunnerService> _logger;
        public BacktestRunnerService(ILogger<BacktestRunnerService> logger)
        {
            _logger = logger;
        }

        public override Task<BacktestOutput> RunBacktest(BacktestRequest request, ServerCallContext context)
        {
            BacktestOutput output = GrpcServer.BacktestConsole.Compute(request);
            return Task.FromResult(output);
        }
    }
}