/**
 * Class implements the transport level of OSI model.
 *
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2020, Sergey Baigudin, Baigudin Software
 */
#ifndef SYS_IPC_BASE_HPP_
#define SYS_IPC_BASE_HPP_

#include "Object.hpp"
#include "sys.IpcPacket.hpp"
#include "api.Read.hpp"
#include "lib.String.hpp"

#if EOOS_CPP_STANDARD < 2011
#error "C++ language standard less than C++11 is not supported"
#endif

namespace eoos
{
    namespace sys
    {         
        class IpcBase : public Object<>
        {
            typedef ::eoos::Object<> Parent;
            
        public:

            /**
             * Constructor.
             *
             * @param dbPath - Path to a dir contains FIFO files.
             */
            explicit IpcBase(const lib::String& dbPath) : Object(),
                dbPath_ {dbPath}
            {
                setConstructed( construct() );
            }
            
            /**
             * Destructor.
             */
            virtual ~IpcBase() noexcept {}
        
            /**        
             * Copy constructor.
             */
            IpcBase(const IpcBase&) = delete;
        
            /**        
             * Move constructor.
             */
            IpcBase(IpcBase&&) = delete;
        
            /**        
             * Copy assignment operator.
             */
            IpcBase& operator=(const IpcBase&) = delete;
        
            /**        
             * Move assignment operator.
             */             
            IpcBase& operator=(IpcBase&&) = delete;
            
            /**
             * Tests if this object has been constructed.
             *
             * @return true if object has been constructed successfully.
             */
            bool_t isConstructed() const override
            {
                return Parent::isConstructed();
            }            
        
            /**
             * Receives a packet.
             *
             * @return a packet of data, or NULLPTR if an error occurred.
             * @note the packet returned must be deleted by caller.
             */
            IpcPacket* receive() noexcept try
            {
                if( not isConstructed() )
                {
                    return NULLPTR;
                }
                bool_t isAccepted {false};
                IpcPacket* packet {NULLPTR};
                do{
                    packet = new IpcPacket( getReedSrteam() );
                    // Test if no memory for a packet
                    if(packet == NULLPTR)
                    {
                        break;
                    }
                    // Test if the packet broken
                    if(not packet->isConstructed())
                    {
                        break;
                    }
                    // Test if the packet has wrong ID
                    IpcId const selfId = getIpcId();
                    IpcId const dstId = packet->getDestination();
                    if(selfId != dstId)
                    {
                        break;
                    }
                    // Accept the packet
                    isAccepted = true;
                } while(false);
                if( not isAccepted )
                {
                    if(packet != NULLPTR)
                    {
                        delete packet;
                    }
                    packet = NULLPTR;
                }
                return packet;
            } catch (...) {
                return NULLPTR;
            }
        
        protected:
        
            /**
             * Gets a path to a FIFO file.
             *
             * TODO: The function has to return "/name" or "\\name"
             *
             * @param id - An IPC Identifier.
             * @return a path to a new client FIFO file.
             */
            lib::String getFilePath(const IpcId& id)
            {
                lib::String path {dbPath_};
                if( IpcId::isServerId(id) )
                {
                    path = path + "server-fifo";
                } 
                else 
                {
                    IpcId::Type const identifier {id};
                    lib::String str;
                    str.convert<IpcId::Type>(identifier, 10);
                    path = path + "/client-fifo-" + str; // (std::to_string(identifier)).c_str();
                }
                return path;
            }
        
        private:
        
            /**
             * Gets a reading stream.
             *
             * @return a stream for receiving data.
             */
            virtual api::Read& getReedSrteam() = 0;
        
            /**
             * Gets a self IPC Identifier.
             *
             * @return a self IPC Identifier.
             */
            virtual IpcId getIpcId() const = 0;
        
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
                    res = true;
                } while(false);
                return res;
            }
        
            /**
             * Path to a dir contains FIFO files.
             */
            lib::String dbPath_;
        };
    }
}

#endif // SYS_IPC_BASE_HPP_
