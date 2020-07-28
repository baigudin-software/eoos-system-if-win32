/**
 * Class implements IPC packet.
 *
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2020, Sergey Baigudin, Baigudin Software
 */
#ifndef SYS_IPC_PACKET_HPP_
#define SYS_IPC_PACKET_HPP_

#include <vector>
#include "Object.hpp"
#include "sys.IpcId.hpp"
#include "api.Read.hpp"
#include "lib.Align.hpp"

namespace eoos
{
    namespace sys
    {
        class IpcPacket final : public Object<>
        {
            typedef ::eoos::Object<> Parent;            
            
        public:

            /**
             * Constructor a packet.
             *
             * @param sourceId - An IPC Identifier.
             * @param destinationId - An IPC Identifier.
             */
            IpcPacket(const IpcId& sourceId, const IpcId& destinationId) : Object(),
                header_ {sourceId, destinationId}
            {
                setConstructed( construct() );
            }
        
            /**
             * Constructor a packet.
             *
             * @param stream - An input stream.
             */
            explicit IpcPacket(const api::Read& stream) : Object(),
                header_ {stream}
            {
                setConstructed( construct(&stream) );
            }
        
            /**
             * Destructor.
             */
            virtual ~IpcPacket() {}
        
            /**
             * Copy constructor.
             */
            IpcPacket(const IpcPacket&) = delete;
        
            /**
             * Move constructor.
             */
            IpcPacket(IpcPacket&&) = default;
        
            /**
             * Copy assignment operator.
             */
            IpcPacket& operator=(const IpcPacket&) = delete;
        
            /**
             * Move assignment operator.
             */
            IpcPacket& operator=(IpcPacket&&) = delete;
            
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
             * Returns source IPC Identifier of this packet.
             *
             * @returns IPC Identifier.
             */
            IpcId getSource()
            {
                IpcId::Type const srcId {header_.srcId};
                return IpcId(srcId);
            }
        
            /**
             * Returns destination IPC Identifier of this packet.
             *
             * @returns IPC Identifier.
             */
            IpcId getDestination()
            {
                IpcId::Type const dstId {header_.dstId};
                return IpcId(dstId);
            }
        
            /**
             * Returns the packet payload data.
             *
             * @returns Pointer to the first byte of the data.
             */
            void* getPayload()
            {
                if( not isConstructed() || not isReady() ) 
                {
                    return NULLPTR;
                }
                return payload_.data() + sizeof(header_);
            }
        
            /**
             * Returns the packet payload data size.
             *
             * @returns Size of the packet in Bytes.
             */
            size_t getPayloadSize() const
            {
                if( not isConstructed() || not isReady() ) 
                {
                    return 0;
                }
                return size_.emplaced - sizeof(header_);
            }
        
            /**
             * Returns the protocol data unit.
             *
             * @returns Pointer to the first byte of the packet.
             */
            const void* getPacket() const
            {
                if( not isConstructed() || not isReady() ) 
                {
                    return NULLPTR;
                }
                return payload_.data();
            }
        
            /**
             * Returns the protocol data unit size.
             *
             * @returns Size of the packet in Bytes.
             */
            size_t getPacketSize() const
            {
                if( not isConstructed() || not isReady() ) 
                {
                    return 0;
                }
                return size_.emplaced;
            }
        
            /**
             * Reserves space in the packet payload.
             *
             * NOTE: This function will return false if emplace() called.
             *
             * @param size - Size in Bytes for reserving.
             * @returns true if the requested size is reserved.
             */
            bool_t reserve(size_t const size) noexcept try
            {
                if( not isConstructed() ) 
                {
                    return false;
                }
                if( not isReserving_ ) 
                {
                    return false;
                }
                size_.reserved += size;
                return true;
            } catch (...) {
                return false;
            }
        
            /**
             * Emplaces data into the payload.
             *
             * NOTE: If this function called, reserve() will return false.
             *
             * @param stream - an input stream.
             * @returns true if the data from the stream is emplaced.
             */
            bool_t emplace(const api::Read& stream) noexcept try
            {
                if( not isConstructed() ) 
                {
                    return false;
                }
                bool_t res {false};
                do{
                    bool_t const isPrepared = preparePayload();
                    if( not isPrepared )
                    {
                        break;
                    }
                    // Read all data from stream
                    size_t const sizeNeed {size_.reserved - size_.emplaced};
                    size_t const sizeRead {stream.read(&payload_[size_.emplaced], sizeNeed)};
                    size_.emplaced += sizeRead;
                    if(sizeRead != sizeNeed)
                    {
                        break;
                    }
                    res = true;
                } while (false);
                // Set the packet not to be constructed if the emplacing faild
                if(res == false) 
                {
                    setConstructed(false);
                }
                return res;
            } catch (...) {
                return false;
            }
        
            /**
             * Emplaces data into the payload.
             *
             * NOTE: If this function called, rserve() will return false.
             *
             * @param data - Pointer to data.
             * @param size - Size of data in Bytes.
             * @returns true if the data is emplaced.
             */
            bool_t emplace(const void* const data, size_t const size) noexcept try
            {
                if( not isConstructed() ) 
                {
                    return false;
                }
                bool_t res {false};
                do{
                    bool_t const isPrepared = preparePayload();
                    if( not isPrepared )
                    {
                        break;
                    }
                    // Check avalible size in the payload
                    size_t const sizeLeft = size_.reserved - size_.emplaced;
                    if(size > sizeLeft)
                    {
                        break;
                    }
                    // Push data into the payload
                    for(size_t i=0; i<size; i++)
                    {
                        const uint8_t* const buf = reinterpret_cast<const uint8_t*>(data);
                        payload_.push_back(buf[i]);
                    }
                    size_.emplaced += size;
                    res = true;
                } while (false);
                // Set the packet not to be constructed if the emplacing faild
                if(res == false) 
                {
                    setConstructed(false);
                }
                return res;
            } catch (...) {
                return false;
            }
        
        private:
        
            /**
             * Prepares the payload for loading data.
             *
             * NOTE: If this function called, reserve() will return false.
             *
             * @returns true if the payload is prepared.
             */
            bool_t preparePayload()
            {
                if( not isReserving_ )
                {
                    return true;
                }
                // Prepare the payload, emplace the header, and close the reserving
                bool_t res {false};
                bool_t const isReserved {reserve(sizeof(header_))};
                if( isReserved ) 
                {
                    isReserving_ = false;
                    payload_.resize(size_.reserved);
                    header_.size = size_.reserved - sizeof(header_);
                    bool_t const isEmplaced {emplace(&header_, sizeof(header_))};
                    if(isEmplaced)
                    {
                        res = true;
                    }
                }
                return res;
            }
        
            /**
             * Tests if this packet is ready.
             *
             * @returns true if the reserving is closed and all the reserved size is emplaced.
             */
            bool_t isReady() const
            {
                if( isReserving_ ) 
                {
                    return false;
                }
                else if( size_.reserved != size_.emplaced )
                {
                    return false;
                }
                else 
                {
                    return true;
                }
            }
        
            /**
             * Constructs this object.
             *
             * @param stream - An input stream.
             * @returns true if this object has been constructed successfully.
             */             
            bool_t construct(const api::Read* const stream = NULLPTR)
            {
                bool_t res {false};
                do{
                    if( not isConstructed() )
                    {
                        break;
                    }
                    // Reserve size in this packet set in the header
                    bool_t const isReserved {reserve(header_.size)};
                    if( not isReserved )
                    {
                        break;
                    }
                    // Emplace data in this packet from a given stream
                    if( stream != NULLPTR )
                    {
                        bool_t const isEmplaced {emplace(*stream)};
                        if( not isEmplaced )
                        {
                            break;
                        }
                    }
                    res = true;
                }while(false);
                return res;
            }
        
            /**
             * This packet header.
             */
            struct Header
            {
                /**
                 * Constructor.
                 *
                 * @param sourceId - An IPC Identifier.
                 * @param destinationId - An IPC Identifier.
                 */
                Header(const IpcId& sourceId, const IpcId& destinationId) :
                    srcId { sourceId },
                    dstId { destinationId }
                {
        
                }
        
                /**
                 * Constructor.
                 *
                 * @param stream - An input stream.
                 */
                explicit Header(const api::Read& stream)
                {
                    stream.read(this, sizeof(Header));
                }
        
                /**
                 * Synchronization value of this packet header.
                 */
                static const uint32_t SYNC {0x55AAAA55};
        
                /**
                 * Synchronization value of the packet.
                 */
                lib::Align<uint32_t> sync {SYNC};
                
                /**
                 * Source ID.
                 */
                lib::Align<IpcId::Type> srcId {0};
                
                /**
                 * Destination ID.
                 */
                lib::Align<IpcId::Type> dstId {0};
                
                /**
                 * Data size of user data of the packet.
                 */
                lib::Align<size_t> size {0};
            };
            
            /**
             * Reservation size.
             */
            struct ReservationSize
            {
                size_t reserved {0};
                size_t emplaced {0};
            };
        
            /**
             * This packet header.
             */
            Header header_;
            
            /**
             * Packet data.
             */
            std::vector<uint8_t> payload_ {};
            
            /**
             * Reservation size.
             */
            ReservationSize size_;
            
            /**
             * Size reserving stage in process.
             */
            bool_t isReserving_ {true};
        };
}
}

#endif // SYS_IPC_PACKET_HPP_
