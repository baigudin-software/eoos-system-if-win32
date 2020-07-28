/**
 * Class implements the transport level of OSI model.
 *
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2020, Sergey Baigudin, Baigudin Software
 */
#ifndef SYS_IPC_CLIENT_HPP_
#define SYS_IPC_CLIENT_HPP_

#include "sys.IpcBase.hpp"
#include "sys.Fifo.hpp"

#if EOOS_CPP_STANDARD < 2011
#error "C++ language standard less than C++11 is not supported"
#endif

namespace eoos
{
    namespace sys
    {
        class IpcClient final : public IpcBase
        {
            
        public:
        
            /**
             * Constructor.
             *
             * @param id - a unique IPC Identifier of the client for the Database.
             * @param dbPath - Database path to a dir contains FIFO files.
             */
            explicit IpcClient(IpcId id, const String& dbPath) noexcept try : IpcBase(dbPath),
                clientId_ {id}
            {
                setConstructed( construct() );
            } catch (...) {
                setConstructed( false );
            }
        
            /**
             * Destructor.
             */
            virtual ~IpcClient() noexcept {}
        
            /**
             * Copy constructor.
             */
            IpcClient(const IpcClient&) = delete;
        
            /**
             * Move constructor.
             */
            IpcClient(IpcClient&&) = delete;
        
            /**
             * Copy assignment operator.
             */
            IpcClient& operator=(const IpcClient&) = delete;
        
            /**
             * Move assignment operator.
             */
            IpcClient& operator=(IpcClient&&) = delete;
            
            /**
             * Sends data to the server.
             *
             * @param data - Pointer to data.
             * @param size - Size of data in Bytes.
             * @return true if the data sent.
             */
            bool_t send(const void* const data, size_t const size) noexcept try
            {
                if( not isConstructed() )
                {
                    return false;
                }
                if( data == NULLPTR || size == 0 )
                {
                    return false;
                }
                IpcPacket packet {clientId_, serverId_};
                bool_t isDone {false};
                isDone = packet.reserve(size);
                if( not isDone )
                {
                    return false;
                }
                isDone = packet.emplace(data, size);
                if( not isDone )
                {
                    return false;
                }
                const void* const packetData {packet.getPacket()};
                size_t const packetSize {packet.getPacketSize()};
                size_t const sentSize { txFifo_.write(packetData, packetSize) };
                return sentSize == packetSize;
            } catch (...) {
                return false;
            }
        
        private:
        
            /**
             * Gets a reading stream.
             *
             * @return a stream for receiving data.
             */
            api::Read& getReedSrteam() override
            {
                return rxFifo_;
            }
        
            /**
             * Gets a self IPC Identifier.
             *
             * @return a self IPC Identifier.
             */
            IpcId getIpcId() const override
            {
                return clientId_;
            }
        
            /**
             * Constructs this object.
             *
             * @return true if this object has been constructed successfully.
             */
            bool_t construct()
            {
                bool_t res {false};
                do{
                    if( not isConstructed() )
                    {
                        break;
                    }
                    if( not rxFifo_.isConstructed() )
                    {
                        break;
                    }
                    if( not txFifo_.isConstructed() )
                    {
                        break;
                    }
                    res = true;
                }while(false);
                return res;
            }
        
            /**
             * This client IPC Identifier
             */
            IpcId clientId_;
            
            /**
             * The server IPC Identifier
             */
            IpcId serverId_ {IpcId::getServerId()};
            
            /**
             * RX FIFO for receiving a server response.
             */
            Fifo rxFifo_ {getFilePath(clientId_),
                Fifo::Flag(Fifo::Flag::READ
                         | Fifo::Flag::BLOCK
                         | Fifo::Flag::REMOVE
                         | Fifo::Flag::CREATE )
            };
            
            /**
             * TX FIFO for transmiting to a server.
             */
            Fifo txFifo_ {getFilePath(serverId_),
                Fifo::Flag(Fifo::Flag::WRITE
                         | Fifo::Flag::BLOCK)
            };
        };
    }
}

#endif // SYS_IPC_CLIENT_HPP_
