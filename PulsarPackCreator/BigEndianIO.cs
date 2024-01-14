using System;
using System.Buffers.Binary;
using System.IO;

namespace PulsarPackCreator
{
    public class BigEndianWriter : BinaryWriter
    {
        public BigEndianWriter(Stream stream) : base(stream) { }
        public override void Write(double value)
        {
            Span<byte> buffer = stackalloc byte[sizeof(double)];
            BinaryPrimitives.WriteDoubleBigEndian(buffer, value);
            OutStream.Write(buffer);
        }

        public override void Write(short value)
        {
            Span<byte> buffer = stackalloc byte[sizeof(short)];
            BinaryPrimitives.WriteInt16BigEndian(buffer, value);
            OutStream.Write(buffer);
        }
        public override void Write(ushort value)
        {
            Span<byte> buffer = stackalloc byte[sizeof(ushort)];
            BinaryPrimitives.WriteUInt16BigEndian(buffer, value);
            OutStream.Write(buffer);
        }

        public override void Write(int value)
        {
            Span<byte> buffer = stackalloc byte[sizeof(int)];
            BinaryPrimitives.WriteInt32BigEndian(buffer, value);
            OutStream.Write(buffer);
        }

        public override void Write(uint value)
        {
            Span<byte> buffer = stackalloc byte[sizeof(uint)];
            BinaryPrimitives.WriteUInt32BigEndian(buffer, value);
            OutStream.Write(buffer);
        }

        public override void Write(long value)
        {
            Span<byte> buffer = stackalloc byte[sizeof(long)];
            BinaryPrimitives.WriteInt64BigEndian(buffer, value);
            OutStream.Write(buffer);
        }
        public override void Write(ulong value)
        {
            Span<byte> buffer = stackalloc byte[sizeof(ulong)];
            BinaryPrimitives.WriteUInt64BigEndian(buffer, value);
            OutStream.Write(buffer);
        }

        public override void Write(float value)
        {
            Span<byte> buffer = stackalloc byte[sizeof(float)];
            BinaryPrimitives.WriteSingleBigEndian(buffer, value);
            OutStream.Write(buffer);
        }

        public override void Write(Half value)
        {
            Span<byte> buffer = stackalloc byte[sizeof(ushort) /* = sizeof(Half) */];
            BinaryPrimitives.WriteHalfBigEndian(buffer, value);
            OutStream.Write(buffer);
        }
    }

    public class BigEndianReader : BinaryReader
    {
        public BigEndianReader(Stream stream) : base(stream) { }
        private static float ReverseEndianness(float value)
        {
            byte[] bytes = BitConverter.GetBytes(value);
            Array.Reverse(bytes);
            float ret = BitConverter.ToSingle(bytes, 0);
            return ret;
        }
        private static double ReverseEndianness(double value)
        {
            byte[] bytes = BitConverter.GetBytes(value);
            Array.Reverse(bytes);
            double ret = BitConverter.ToDouble(bytes, 0);
            return ret;
        }
        public override short ReadInt16() => BinaryPrimitives.ReverseEndianness(base.ReadInt16());
        public override ushort ReadUInt16() => BinaryPrimitives.ReverseEndianness(base.ReadUInt16());
        public override int ReadInt32() => BinaryPrimitives.ReverseEndianness(base.ReadInt32());
        public override uint ReadUInt32() => BinaryPrimitives.ReverseEndianness(base.ReadUInt32());
        public override long ReadInt64() => BinaryPrimitives.ReverseEndianness(base.ReadInt64());
        public override ulong ReadUInt64() => BinaryPrimitives.ReverseEndianness(base.ReadUInt64());
        public override float ReadSingle() => ReverseEndianness(base.ReadSingle());
        public override double ReadDouble() => ReverseEndianness(base.ReadDouble());
    }

}
