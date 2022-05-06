using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Threading.Tasks.Dataflow;

namespace DataflowTry
{
    class Program
    {
        static void Main(string[] args)
        {
            TestExceptions();
        }

        private static void TestExceptions()
        {
            var generator = new Random();
            Action<int> fn = n =>
            {
                var sleepTime = 500 + generator.Next(1000);
                Console.WriteLine("{0}: sleep time {1}ms", n, sleepTime);

                var thisTask = Task.Delay(1000);
                if (Task.WaitAny(new Task[] { thisTask }, sleepTime) == -1)
                {
                    //var message = n.ToString() + ": stop by timeout";
                    //Console.WriteLine(message);
                    //throw new TimeoutException(message);
                }

                Console.WriteLine("{0}: process", n);
                if (generator.Next(4) == 0)
                {
                    //var message = n.ToString() + ": stop by error";
                    //Console.WriteLine(message);
                    //throw new Exception(message);
                }
            };

            var cts = new CancellationTokenSource();
            var opts = new ExecutionDataflowBlockOptions
            {
                MaxDegreeOfParallelism = 2,
                CancellationToken = cts.Token
            };

            var actionBlock = new ActionBlock<int>(fn, opts);
            actionBlock.Completion.ContinueWith(task =>
            {
                if (task.IsFaulted)
                    Console.WriteLine("Faulted with:" + task.Exception.InnerException.Message);
            });

            for (int i = 0; i < 20; i++)
            {
                actionBlock.Post(i);
                if (i == 10)
                {
                    //actionBlock.Complete(); //No more posted - but which were posted - are executed
                    //cts.Cancel(); //Nothing is processed - because everything is canceled
                }
            }
            Console.WriteLine("Wait a little");
            Thread.Sleep(3000);
            Console.WriteLine("Stop everything");
            //case 0 - everything, which is already posted, will be processed
            actionBlock.Complete();
            actionBlock.Completion.Wait();
            //case 1
            cts.Cancel(); // stops processing
            //actionBlock.Completion.Wait(); // Raises exception - TaskCanceled
            //case 2
            //((IDataflowBlock)actionBlock).Fault(new Exception("Stop it now"));
            //actionBlock.Completion.Wait(); // Raises exception if faulted
            Console.WriteLine("Stop everything Done");
            Thread.Sleep(20000);
            Console.WriteLine("Done");
        }
    }
}