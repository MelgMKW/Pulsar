using Kamek.Commands;
using System.IO;

namespace Kamek.Hooks
{
    class WriteHook : Hook
    {
        public WriteHook(Linker.HookData data, AddressMapper mapper)
        {
            uint dataType = data.type;
            Word[] args = data.args;
            bool isConditional = dataType == 2;
            bool isRegion = dataType == 3;
            if (args.Length != ((isConditional || isRegion) ? 4 : 3))
                throw new InvalidDataException("wrong arg count for WriteCommand");

            if (isRegion)
            {
                char region = (char)GetValueArg(args[3]).Value;
                if (region != Program._curVer.ToCharArray()[0]) return;
            }
            // expected args:
            //   address  : pointer to game code
            //   value    : value, OR pointer to game code or to Kamek code
            //   original : value, OR pointer to game code or to Kamek code
            var type = (WriteCommand.Type)GetValueArg(args[0]).Value;
            Word address, value;
            Word? original = null;

            if (isRegion) address = args[1];
            else address = GetAbsoluteArg(args[1], mapper);
            if (type == WriteCommand.Type.Pointer)
            {
                value = GetAnyPointerArg(args[2], mapper);
                if (isConditional)
                    original = GetAnyPointerArg(args[3], mapper);
            }
            else
            {
                value = GetValueArg(args[2]);
                if (isConditional)
                    original = GetValueArg(args[3]);
            }

            Commands.Add(new WriteCommand(address, value, type, original));
        }
    }
}
