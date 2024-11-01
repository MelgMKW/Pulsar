using System.IO;

namespace Kamek.Hooks
{
    class BranchHook : Hook
    {
        public BranchHook(Linker.HookData data, AddressMapper mapper)
        {
            uint dataType = data.type;
            Word[] args = data.args;
            bool isLink = dataType == 5 || dataType == 7;
            bool isRegion = dataType == 6 || dataType == 7;
            if (args.Length != (isRegion ? 3 : 2))
                throw new InvalidDataException("wrong arg count for BranchCommand");

            if (isRegion)
            {
                char region = (char)GetValueArg(args[3]).Value;
                if (region != Program._curVer.ToCharArray()[0]) return;
            }
            // expected args:
            //   source : pointer to game code
            //   dest   : pointer to game code or to Kamek code
            Word source;
            if (isRegion) source = args[0];
            else source = GetAbsoluteArg(args[0], mapper);
            var dest = GetAnyPointerArg(args[1], mapper);

            Commands.Add(new Commands.BranchCommand(source, dest, isLink));
        }
    }
}
